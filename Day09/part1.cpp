#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
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

bool sum_of_two_previous(vector<uint64_t> values, int result) {
    std::sort(values.begin(), values.end());

    std::vector<uint64_t>::iterator lowerBound = values.begin();
    std::vector<uint64_t>::iterator upperBound = values.end() - 1;

    int currentValue;
    while (lowerBound != upperBound) {
        currentValue = (*lowerBound) + (*upperBound);
        if ((*lowerBound) + (*upperBound) == result) {
            return true;
        }
        else if (currentValue > result) {
            upperBound = upperBound - 1;
        }
        else if (currentValue < result) {
            lowerBound = lowerBound + 1;
        }
    }
    return false;
}

int main() {
    vector<string> all_numbers = readFile("input.txt");
    int length_preamble = 25;
    vector<uint64_t> current_numbers;
    for (int i = 0; i < all_numbers.size(); i++) {
        current_numbers.push_back(stol(all_numbers[i]));
    }
    for (int i = length_preamble; i < all_numbers.size(); i++) {
        vector<uint64_t> subvector(current_numbers.begin() + (i - length_preamble), current_numbers.begin() + i);
        bool sum_possible = sum_of_two_previous(subvector, current_numbers[i]);
        if (!sum_possible) {
            cout << "Number " << current_numbers[i] << " has no sum of in the previous " << length_preamble << " numbers" << endl;
            break;
        }
    }
}