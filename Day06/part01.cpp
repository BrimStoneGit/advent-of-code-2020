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
    int sum_of_unique_answers = 0;

    for (int i = 0; i < answers.size(); i++) {
        if (answers[i] != "") {
            for (int j = 0; j < answers[i].size(); j++) {
                char_occurences[answers[i][j] - 'a'] = 1;
            }
        }
        else {
            sum_of_unique_answers += std::accumulate(char_occurences.begin(), char_occurences.end(), 0);
            std::fill(char_occurences.begin(), char_occurences.end(), 0);
        }
    }

    cout << "The result is " << sum_of_unique_answers << endl;
    return 0;
}