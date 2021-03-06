#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>
#include <map>
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

void set_adjacency_matrix_values_for_given_bags(string input_bag, string containing_bag, int **adjacency_matrix, map<string, int> bag_to_int) {

    while (containing_bag != "") {
        
        string delimiter;

        if (containing_bag.find(",") == string::npos) {
            delimiter = ".";
        }
        else {
            delimiter = ",";
        }

        int value = containing_bag[0] - '0';
        if (value <= 0 || value >= 10) {
            break;
        }
        string current_bag_contains;
        if (value != 1) {
            // "1 shiny silver bag", but "3 shiny silver bags". Cutting of the plural 's'
            current_bag_contains = containing_bag.substr(2, containing_bag.find(delimiter) - 3);
        }
        else {
            current_bag_contains = containing_bag.substr(2, containing_bag.find(delimiter) - 2);
        }
        int int_current_bag_contains = bag_to_int[current_bag_contains];
        int int_input_bag = bag_to_int[input_bag];
        adjacency_matrix[int_input_bag][int_current_bag_contains] = value;
        if (delimiter == ",") {
            containing_bag = containing_bag.substr(containing_bag.find(delimiter) + 2, containing_bag.size());
        } else {
            containing_bag = containing_bag.substr(containing_bag.find(delimiter) + 1, containing_bag.size());
        }   
    }
}

set<int> bags_containing_given_bag(int input_bag_id, int **adj_matrix, int adj_matrix_length) {
    set<int> result;
    for (int i = 0; i < adj_matrix_length; i++) {
        if (adj_matrix[i][input_bag_id] != 0) {
            cout << "Going into recursion to id " << i << endl;
            set<int> recursive_result = bags_containing_given_bag(i, adj_matrix, adj_matrix_length);
            cout << "Got out of recursion. Adding " << i << endl;
            recursive_result.insert(i);
            result.insert(recursive_result.begin(), recursive_result.end());
        }
    }
    return result;
}

int main() {
    std::map<string, int> bag_to_int;
    std::map<int, string> reverse_int_to_bag;
    std::vector<string> vec_bags = readFile("input.txt");
    int **adj_matrix = new int*[vec_bags.size()];

    for (int i = 0; i < vec_bags.size(); i++) {
        adj_matrix[i] = new int[vec_bags.size()];
        // cut of the "s" at the end of "bags"
        bag_to_int[vec_bags[i].substr(0, vec_bags[i].find(" contain ") - 1)] = i;
        reverse_int_to_bag[i] = vec_bags[i].substr(0, vec_bags[i].find(" contain ") - 1);
    }

    for (int i = 0; i < vec_bags.size(); i++) {
        string current_bag_name =  vec_bags[i].substr(0, vec_bags[i].find(" contain ") - 1);
        string contains_relation = vec_bags[i].substr(vec_bags[i].find(" contain ") + 9, vec_bags[i].size());
        set_adjacency_matrix_values_for_given_bags(current_bag_name, 
                                            contains_relation,
                                            adj_matrix,
                                            bag_to_int);
    }

    int golden_bag_id = bag_to_int["shiny gold bag"];
    set<int> bags_holding_golden_bag = bags_containing_given_bag(golden_bag_id, adj_matrix, vec_bags.size());
    cout << "Number of bags eventually containing shiny gold bag is: " << bags_holding_golden_bag.size() << endl;

}