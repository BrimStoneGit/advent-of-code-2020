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
    while ( getline(infile, temp) ) {
        parsed_vec.push_back(temp);
    }
    return parsed_vec;
}

int main() {
    std::vector<string> vec_ops = readFile("input.txt");
    int instruction_pointer = 0;
    int accumulator = 0;
    vector<int> instruction_count(vec_ops.size(), 0);

    while (instruction_count[instruction_pointer] == 0) {
        instruction_count[instruction_pointer] += 1;
        string whole_command = vec_ops[instruction_pointer];
        string instruction = whole_command.substr(0, 3);
        int amount = std::stoi(whole_command.substr(4, whole_command.size()));
        if (instruction == "nop") {
            instruction_pointer += 1;
        }
        else if (instruction == "acc") {
            accumulator += amount;
            instruction_pointer += 1;
        }
        else if (instruction == "jmp") {
            instruction_pointer += amount;
        }
    }
    cout << "Accumulator steht auf " << accumulator << endl;
    return 0;
}