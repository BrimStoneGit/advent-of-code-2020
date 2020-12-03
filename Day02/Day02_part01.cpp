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
    std::vector<string> ranges;
    std::vector<string> characters;
    std::vector<string> passwords;
    std::ifstream infile("input.txt");
    string range;
    string character;
    string passwd;
    while (infile >> range >> character >> passwd)
    {
        ranges.push_back(range);
        characters.push_back(character);
        passwords.push_back(passwd);
    }

    int valid_passwords = 0;

    string delimiter_amount = "-";
    for (int i = 0; i < ranges.size(); i++) {
        // cout << i << endl;
        int lower_bound = std::stoi(ranges[i].substr(0, ranges[i].find(delimiter_amount)));
        int upper_bound = std::stoi(ranges[i].substr(ranges[i].find(delimiter_amount) + 1, ranges[i].size()));
        char current_char = characters[i].at(0);
        if ( lower_bound <= std::count(passwords[i].begin(), passwords[i].end(), current_char) && std::count(passwords[i].begin(), passwords[i].end(), current_char) <= upper_bound) 
        {
            valid_passwords += 1;
        }
    }
    cout << valid_passwords << endl;

}