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

int main() {
    vector<string> adapters = readFile("input.txt");
    vector<int> int_adapters;
    int_adapters.push_back(0);
    for (int i = 0; i < adapters.size(); i++) {
        int_adapters.push_back(stoi(adapters[i]));
    }
    std::sort(int_adapters.begin(), int_adapters.end());
    int_adapters.push_back(int_adapters.back() + 3);
    int one_jolt_diff = 0;
    int three_jolt_diff = 0;
    for (int i = 1; i < int_adapters.size(); i++) {
        if (int_adapters[i] - int_adapters[i - 1] == 1) {
            one_jolt_diff++;
        }
        else if (int_adapters[i] - int_adapters[i - 1] == 3) {
            three_jolt_diff++;
        }
    }
    cout << "Solution: " << one_jolt_diff * three_jolt_diff << endl;

    return 0;
}