#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <set>
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
    // set<int> fixed_value_indices;
    // fixed_value_indices.insert(0);
    // for (int i = 0; i < int_adapters.size(); i++) {
    //     if (int_adapters[i + 1] - int_adapters[i] >= 3) {
    //         fixed_value_indices.insert(i);
    //         fixed_value_indices.insert(i + 1);
    //     }
    // }

    // for (int i = 0; i < int_adapters.size(); i++) {
    //     bool is_in = fixed_value_indices.find(i) != fixed_value_indices.end();
    //     cout << "Value: " << int_adapters[i] << " with index " << i << " and it being in the set is " << is_in << endl;
    // }

    vector<uint64_t> paths_till_index(int_adapters.back() + 1, 0);
    paths_till_index[0] = 1;
    for (int i = 0; i < int_adapters.size(); i++) {
        paths_till_index[int_adapters[i] + 1] += paths_till_index[int_adapters[i]];
        paths_till_index[int_adapters[i] + 2] += paths_till_index[int_adapters[i]];
        paths_till_index[int_adapters[i] + 3] += paths_till_index[int_adapters[i]];
    }

    cout << "Solution is " << paths_till_index[int_adapters.back()] << endl;




    return 0;
}