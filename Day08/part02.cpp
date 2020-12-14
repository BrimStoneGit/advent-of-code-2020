#include <iostream>
#include <tuple>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

typedef struct {
    int instruction_pointer;
    int accumulator;
    vector<int> instruction_count;
} system_state;

std::vector<string> readFile(string fileName) {
    std::vector<string> parsed_vec;
    std::ifstream infile(fileName);
    string temp;
    while ( getline(infile, temp) ) {
        parsed_vec.push_back(temp);
    }
    return parsed_vec;
}

std::tuple<bool,int> terminates(system_state state, vector<string> program) {
    do {
        state.instruction_count[state.instruction_pointer] += 1;
        string whole_command = program[state.instruction_pointer];
        string instruction = whole_command.substr(0, 3);
        int amount = std::stoi(whole_command.substr(4, whole_command.size()));
        if (instruction == "nop") {
            state.instruction_pointer += 1;
        }
        else if (instruction == "acc") {
            state.accumulator += amount;
            state.instruction_pointer += 1;
        }
        else if (instruction == "jmp") {
            state.instruction_pointer += amount;
        }
        cout << "Instruction number " << state.instruction_pointer << " of " << program.size() << endl;
        cout << "Current instruction count is " << state.instruction_count[state.instruction_pointer] << endl;

    } while (state.instruction_pointer < program.size() && state.instruction_count[state.instruction_pointer] == 0);

    if (state.instruction_pointer >= program.size()) {
        return std::make_tuple(true, state.accumulator);
    }
    else if (state.instruction_count[state.instruction_pointer] != 0) {
        return std::make_tuple(false, -1);
    }
}

int main() {
    std::vector<string> vec_ops = readFile("input.txt");
    system_state current_state;
    current_state.accumulator = 0;
    current_state.instruction_pointer = 0;
    current_state.instruction_count = vector<int>(vec_ops.size(), 0);



    while (true) {
        current_state.instruction_count[current_state.instruction_pointer] += 1;
        string whole_command = vec_ops[current_state.instruction_pointer];
        string instruction = whole_command.substr(0, 3);
        int amount = std::stoi(whole_command.substr(4, whole_command.size()));
        vector<string> modified_ops = vec_ops;
        system_state last_saved_state = current_state;
        
        if (instruction == "acc") {
            current_state.accumulator += amount;
            current_state.instruction_pointer += 1;
        }
        else if (instruction == "nop") {
            modified_ops[current_state.instruction_pointer] = whole_command.substr(4, whole_command.size()).insert(0, "jmp ");
            cout << "Going into termination test" << endl;
            std::tuple<bool, int> result = terminates(last_saved_state, modified_ops);
            if (std::get<0>(result)) {
                cout << "State of the acc is " << std::get<1>(result) << endl;
                break;
            }
            cout << "Didn't terminate" << endl;
            current_state.instruction_pointer += 1;
        }
        else if (instruction == "jmp") {
            modified_ops[current_state.instruction_pointer] = whole_command.substr(4, whole_command.size()).insert(0, "nop ");
            cout << "Going into termination test" << endl;
            std::tuple<bool, int> result = terminates(last_saved_state, modified_ops);
            if (std::get<0>(result)) {
                cout << "State of the acc is " << std::get<1>(result) << endl;
                break;
            }
            cout << "Didn't terminate" << endl;
            current_state.instruction_pointer += amount;
        }
    }
    return 0;
}