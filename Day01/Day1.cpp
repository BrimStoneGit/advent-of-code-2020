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
    std::vector<int> numbers;
    std::ifstream infile("input.txt");
    int current_input;
    while (infile >> current_input)
    {
        numbers.push_back(current_input);
    }
    std::sort(numbers.begin(), numbers.end());

    std::vector<int>::iterator lowerBound = numbers.begin();
    std::vector<int>::iterator upperBound = numbers.end() - 1;

    int currentValue;
    while (lowerBound != upperBound) {
        currentValue = (*lowerBound) + (*upperBound);
        if (currentValue == 2020) {
            cout << *lowerBound * (*upperBound) << endl;
            break;
        }
        else if (currentValue > 2020) {
            upperBound = upperBound - 1;
        }
        else if (currentValue < 2020) {
            lowerBound = lowerBound + 1;
        }
    }

    return 0;

}