#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void printVector(vector<int> inputVec) {
    for (int i = 0; i < inputVec.size(); i++) 
    {
        cout << inputVec[i] << endl;
    }
}

int main() {
    std::vector<string> vec_ranges;
    std::vector<string> vec_characters;
    std::vector<string> vec_passwords;
    std::ifstream infile("input.txt");
    string range;
    string character;
    string passwd;
    while (infile >> range >> character >> passwd)
    {
        vec_ranges.push_back(range);
        vec_characters.push_back(character);
        vec_passwords.push_back(passwd);
    }

    int valid_passwords = 0;

    string delimiter_amount = "-";
    for (int i = 0; i < vec_ranges.size(); i++) {
        // cout << i << endl;
        int first_pos = std::stoi(vec_ranges[i].substr(0, vec_ranges[i].find(delimiter_amount)));
        int sec_pos = std::stoi(vec_ranges[i].substr(vec_ranges[i].find(delimiter_amount) + 1, vec_ranges[i].size()));
        char current_char = vec_characters[i].at(0);
        bool first_cond = current_char == vec_passwords[i].at(first_pos - 1);
        bool sec_cond = current_char == vec_passwords[i].at(sec_pos - 1);
        if ((first_cond || sec_cond) && !(first_cond && sec_cond))
        {
            valid_passwords += 1;
        }
    }
    cout << valid_passwords << endl;

}