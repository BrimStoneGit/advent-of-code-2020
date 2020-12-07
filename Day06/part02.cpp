#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>
using namespace std;

std::vector<string> readFile(string fileName) {
    std::vector<string> parsed_vec;
    std::ifstream infile(fileName);
    string temp;
    while ( getline(infile, temp) ) {
        parsed_vec.push_back(temp);
    }
    parsed_vec.push_back("");
    return parsed_vec;
}

int main() {

    vector<string> answers = readFile("input.txt");

    vector<int> char_occurences(26, 0);
    int sum_of_answers__everyone = 0;
    int index_of_group_beginning = 0;

    for (int i = 0; i < answers.size(); i++) {
        if (answers[i] != "") {
            for (int j = 0; j < answers[i].size(); j++) {
                char_occurences[answers[i][j] - 'a'] += 1;
            }
        }
        else {
            for (int j = 0; j < char_occurences.size(); j++) {
                if (char_occurences[j] == (i - index_of_group_beginning)) {
                    sum_of_answers__everyone += 1;
                }
            }
            std::fill(char_occurences.begin(), char_occurences.end(), 0);
            index_of_group_beginning = i + 1;
        }
    }

    cout << "The result is " << sum_of_answers__everyone << endl;
    return 0;
}