#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

std::vector<string> readFile(string fileName) {
    std::vector<string> parsed_vec;
    std::ifstream infile(fileName);
    string temp;
    while ( getline(infile, temp) ) {
        parsed_vec.push_back(temp);
    }
    return parsed_vec;
}

void printVector(vector<string> *seats) {
    for (int i = 0; i < (*seats).size(); i++) {
        cout << (*seats)[i] << endl;
    }
}

int search_in_direction(vector<string> *seats, int center_x, int center_y, int dir_x, int dir_y) {
    while ((*seats)[center_x + dir_x][center_y + dir_y] == '.') {
        if (center_x + dir_x < 0 || center_y + dir_y < 0 || center_x + dir_x >= (*seats).size() || center_y + dir_y >= (*seats)[0].size()) {
            return 0;
        }
        dir_x += (dir_x > 0) ? 1 : ((dir_x < 0) ? -1 : 0);
        dir_y += (dir_y > 0) ? 1 : ((dir_y < 0) ? -1 : 0);
    }
    if ((*seats)[center_x + dir_x][center_y + dir_y] == '#') {
        return 1;
    }
    else {
        return 0;
    }
}

int count_occupied_seats(vector<string> *seats, int x_pos, int y_pos) {
    int count_of_occupied_seats = 0;
    for (int i = x_pos - 1; i <= x_pos + 1; i++) {
        for (int j = y_pos - 1; j <= y_pos + 1; j++) {
            if (i >= 0 && j >= 0 && i < (*seats).size() && j < (*seats)[0].size() && !(i == x_pos && j == y_pos)) {
                count_of_occupied_seats += search_in_direction(seats, x_pos, y_pos, i - x_pos, j - y_pos);
            }
        }
    }
    return count_of_occupied_seats;
}

char new_seat_state(vector<string> *seats, int x_pos, int y_pos) {
    int count_of_occupied_seats = 0;
    if ((*seats)[x_pos][y_pos] == 'L') {
        count_of_occupied_seats = count_occupied_seats(seats, x_pos, y_pos);
        return (count_of_occupied_seats == 0) ? '#' : 'L';
    }
    else if ((*seats)[x_pos][y_pos] == '#') {
        count_of_occupied_seats = count_occupied_seats(seats, x_pos, y_pos);
        return (count_of_occupied_seats >= 5) ? 'L' : '#';
    }
    return '?';
}

int main() {
    std::vector<string> seats = readFile("input.txt");
    std::vector<string> last_state = seats;
    int32_t iterations = 0;

    do {
        iterations++;
        cout << "iteration nr. " << iterations << endl;
        // printVector(&seats);
        last_state = seats;
        for (int i = 0; i < seats.size(); i++) {
            for (int j = 0; j < seats[i].size(); j++) {
                if (seats[i][j] != '.') {
                    seats[i][j] = new_seat_state(&last_state, i, j);
                }
            }
        }
    } while (!(std::equal(seats.begin(), seats.end(), last_state.begin())));
    int32_t number_of_occupied_seats = 0;
    for (int i = 0; i < seats.size(); i++) {
        for (int j = 0; j < seats[0].size(); j++) {
            number_of_occupied_seats += (seats[i][j] == '#') ? 1 : 0;
        }
    }
    cout << number_of_occupied_seats << endl;
}