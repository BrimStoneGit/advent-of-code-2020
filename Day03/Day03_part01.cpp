#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    std::vector<string> trees;

    std::ifstream infile("input.txt");
    string tree;
    while (infile >> tree)
    {
        trees.push_back(tree);
    }

    int tree_counter = 0;
    int length_of_fields = trees[0].size();

    for ( int i = 1; i < trees.size(); i++) {
        if ( trees[i].at((i * 3) % length_of_fields) == '#') {
            tree_counter++;
        }
    }

    cout << tree_counter << endl;

    return 0;
}