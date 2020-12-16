#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

struct ship_info {
    int64_t north_south;
    int64_t east_west;
    char facing_direction;
};

std::vector<string> readFile(string fileName) {
    std::vector<string> parsed_vec;
    std::ifstream infile(fileName);
    string temp;
    while ( getline(infile, temp) ) {
        parsed_vec.push_back(temp);
    }
    return parsed_vec;
}

void change_direction(ship_info *current_ship, char direction, int32_t amount) {
    vector<char> turning_list = {'N', 'E', 'S', 'W'};
    // trim to range [0, 3]
    amount = (amount % 360) / 90;
    if (direction == 'R') {
        int32_t index_of_direction = (std::distance(turning_list.begin(), std::find(turning_list.begin(), turning_list.end(), current_ship->facing_direction)) + amount) % 4;
        current_ship->facing_direction = turning_list[index_of_direction];
    }
    else if (direction == 'L') {
        int32_t index_of_direction = (std::distance(turning_list.begin(), std::find(turning_list.begin(), turning_list.end(), current_ship->facing_direction)) - amount + 4) % 4;
        current_ship->facing_direction = turning_list[index_of_direction];
    }
}

void parse_command(ship_info *current_ship, string command) {
    cout << command << " || ";
    char direction = command[0];
    int32_t amount = std::stoi(command.substr(1, command.size()));
    switch (direction) {
        case 'E':
            current_ship->east_west += amount;
            break;
        case 'W':
            current_ship->east_west -= amount;
            break;
        case 'N':
            current_ship->north_south += amount;
            break;
        case 'S':
            current_ship->north_south -= amount;
            break;
        case 'F':
            parse_command(current_ship, current_ship->facing_direction + std::to_string(amount));
            break;
        case 'L':
            change_direction(current_ship, 'L', amount);
            break;
        case 'R':
            change_direction(current_ship, 'R', amount);
            break;
        default:
            break;
    }
}

int main() {
    vector<string> commands = readFile("input.txt");
    ship_info current_ship;
    current_ship.north_south = 0;
    current_ship.east_west = 0;
    current_ship.facing_direction = 'E';

    for (int i = 0; i < commands.size(); i++) {
        parse_command(&current_ship, commands[i]);
        cout << current_ship.north_south << " / " << current_ship.east_west << " / " << current_ship.facing_direction << endl;
    }
    cout << endl;
    cout << "State of the ship is " << current_ship.east_west << " and " << current_ship.north_south << endl;
    cout << "Manhatten distance is " << std::abs(current_ship.east_west) + std::abs(current_ship.north_south) << endl;
    return 0;
}