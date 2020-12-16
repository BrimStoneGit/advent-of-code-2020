#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;

struct ship_info {
    int64_t north_south;
    int64_t east_west;
    char facing_direction;
};

struct waypoint {
    int64_t y_coord;
    int64_t x_coord;
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

void calculate_new_waypoint_values(waypoint *current_waypoint, int degrees) {
    // using rotation matrix logic to calculate the rotation
    int x_x = cos(degrees * M_PI / 180.0);
    int y_y = x_x;
    int x_y = sin(degrees * M_PI / 180.0);
    int y_x = (-sin(degrees * M_PI / 180.0));
    int64_t new_x = (current_waypoint->x_coord * x_x) + (current_waypoint->y_coord * x_y);
    int64_t new_y = (current_waypoint->x_coord * y_x) + (current_waypoint->y_coord * y_y);
    current_waypoint->x_coord = new_x;
    current_waypoint->y_coord = new_y;
}

void rotate(waypoint *current_waypoint, char direction, int32_t amount) {
    if (direction == 'R') {
        calculate_new_waypoint_values(current_waypoint, amount);
    }
    else if (direction == 'L') {
        calculate_new_waypoint_values(current_waypoint, -amount);
    }
}

void parse_command(ship_info *current_ship, waypoint *current_waypoint, string command) {
    char direction = command[0];
    int32_t amount = std::stoi(command.substr(1, command.size()));
    switch (direction) {
        case 'E':
            current_waypoint->x_coord += amount;
            break;
        case 'W':
            current_waypoint->x_coord -= amount;
            break;
        case 'N':
            current_waypoint->y_coord += amount;
            break;
        case 'S':
            current_waypoint->y_coord -= amount;
            break;
        case 'F':
            current_ship->east_west += current_waypoint->x_coord * amount;
            current_ship->north_south += current_waypoint->y_coord * amount;
            break;
        case 'L':
            rotate(current_waypoint, 'L', amount);
            break;
        case 'R':
            rotate(current_waypoint, 'R', amount);
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
    waypoint current_waypoint;
    current_waypoint.x_coord = 10;
    current_waypoint.y_coord = 1;


    for (int i = 0; i < commands.size(); i++) {
        parse_command(&current_ship, &current_waypoint, commands[i]);
    }
    cout << abs(current_ship.east_west) + abs(current_ship.north_south) << endl;
    return 0;
}