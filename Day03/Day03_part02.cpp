#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int calculate_trees(int right, int down) {
    std::vector<string> trees;

    std::ifstream infile("input.txt");
    string tree;
    while (infile >> tree)
    {
        trees.push_back(tree);
    }

    int tree_counter = 0;
    int length_of_fields = trees[0].size();

    for ( int i = 1; i < trees.size() / down; i++) {
        if ( trees[i * down].at((i * right) % length_of_fields) == '#') {
            tree_counter++;
        }
    }

    return tree_counter;
}

int main() {
    int tree_counts[5];
    tree_counts[0] = calculate_trees(1, 1);
    tree_counts[1] = calculate_trees(3, 1);
    tree_counts[2] = calculate_trees(5, 1);
    tree_counts[3] = calculate_trees(7, 1);
    tree_counts[4] = calculate_trees(1, 2);
    uint64_t product = 1;
    for (int i = 0; i < 5; i++) {
        product *= tree_counts[i];
    }
    cout << product << endl;
}