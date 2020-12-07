#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

std::vector<string> readFile(string fileName) {
    std::vector<string> parsed_vec;
    std::ifstream infile(fileName);
    string temp;
    while ( infile >> temp ) {
        parsed_vec.push_back(temp);
    }
    return parsed_vec;
}

string boarding_pass_to_binary(string boarding_pass) {
    std::replace(boarding_pass.begin(), boarding_pass.end(), 'F', '0');
    std::replace(boarding_pass.begin(), boarding_pass.end(), 'B', '1');
    std::replace(boarding_pass.begin(), boarding_pass.end(), 'R', '1');
    std::replace(boarding_pass.begin(), boarding_pass.end(), 'L', '0');
    return boarding_pass;
}

int main() {
    std::vector<string> vec_boarding_passes;
    vec_boarding_passes = readFile("input.txt");

    std::vector<int> boarding_pass_list(1023, 0);

    for (int i = 0; i < vec_boarding_passes.size(); i++) {
        string temp_boarding_pass = vec_boarding_passes[i];
        temp_boarding_pass =  boarding_pass_to_binary(temp_boarding_pass);
        int row = stoi(temp_boarding_pass.substr(0, 7), 0, 2);
        int column = stoi(temp_boarding_pass.substr(7, 10), 0, 2);
        int seat_id = row * 8 + column;
        boarding_pass_list[seat_id] = 1;
    }
    for ( int i = 1; i < boarding_pass_list.size() - 1; i++) {
        if (boarding_pass_list[i - 1] == 1 && boarding_pass_list[i + 1] == 1 && boarding_pass_list[i] == 0) {
            cout << "Our seat is " << i << endl;
        }
    }

    return 0;
}