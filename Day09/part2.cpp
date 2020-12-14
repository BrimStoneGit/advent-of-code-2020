#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>
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

uint64_t find_contiguous_set(vector<uint64_t> numbers, uint64_t goal_number) {
    uint64_t lower_bound = 0;
    uint64_t upper_bound = 2;

    while (true) {
        vector<uint64_t> current_range(numbers.begin() + lower_bound, numbers.begin() + upper_bound);
        
        uint64_t sum_of_range = 0;

        std::for_each(current_range.begin(), current_range.end(), [&] (uint64_t n) {
            sum_of_range += n;
        });

        if (sum_of_range < goal_number) {
            upper_bound += 1;
        }
        else if (sum_of_range > goal_number) {
            lower_bound += 1;
        }
        else if (sum_of_range == goal_number) {
            uint64_t biggest_num = 0;
            uint64_t smallest_num = numbers[numbers.size() - 1];
            uint64_t test_sum = 0;
            for (int i = lower_bound; i < upper_bound; i++) {
                test_sum += numbers[i];
                if (numbers[i] > biggest_num) {
                    biggest_num = numbers[i];
                }
                if (numbers[i] < smallest_num) {
                    smallest_num = numbers[i];
                }
            }
            return (smallest_num + biggest_num);
        }
    }
    return 0;
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
            uint64_t sum_of_set = find_contiguous_set(current_numbers, current_numbers[i]);
            cout << "Sum of smallest and biggest number of contiguous set is " << sum_of_set << endl;
            
            break;
        }
    }
}