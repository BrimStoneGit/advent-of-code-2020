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
    while ( getline(infile, temp) )
    {
        std::istringstream iss(temp);
        if (temp != "") {
            string passport_data;
            while (iss >> passport_data) {
                parsed_vec.push_back(passport_data);
            }
        }
        else {
            parsed_vec.push_back(temp);
        }
    }
    // for (int i = 0; i < parsed_vec.size(); i++) {
    //     cout << parsed_vec[i] << endl;
    // }
    parsed_vec.push_back("");
    return parsed_vec;
}

int map_field_to_int(string given_field) {
    if (given_field == "byr") {
        return 0;
    }
    else if (given_field == "iyr") {
        return 1;
    }
    else if (given_field == "eyr") {
        return 2;
    }
    else if (given_field == "hgt") {
        return 3;
    }
    else if (given_field == "hcl") {
        return 4;
    }
    else if (given_field == "ecl") {
        return 5;
    }
    else if (given_field == "pid") {
        return 6;
    }
    else if (given_field == "cid") {
        return 7;
    }
    return 8;
}

int main() {
    std::vector<string> vec_passport;
    vec_passport = readFile("input.txt");

    int count = 0;

    uint8_t result = 0x00;
    // result = result | 0xF0;
    // result = result | 0x0F;
    // printf("result is currently %x\n", result);
    // Bits are representing validity of:
    // byr, iyr, eyr, hgt, hcl, ecl, pid, cid
    // so only 0xFE or 0xFF would be valid



    for (int i = 0; i < vec_passport.size(); i++) {
        string wanted_field = vec_passport[i].substr(0, vec_passport[i].find(":"));
        switch (map_field_to_int(wanted_field)) {
            case 0:
                result = result | 0x80;
                break;
            case 1:
                result = result | 0x40;
                break;
            case 2:
                result = result | 0x20;
                break;
            case 3:
                result = result | 0x10;
                break;
            case 4:
                result = result | 0x08;
                break;
            case 5:
                result = result | 0x04;
                break;
            case 6:
                result = result | 0x02;
                break;
            case 7:
                result = result | 0x01;
                break;
            case 8:
                if (result == 0xFF || result == 0xFE) {
                    count++;
                }
                result = 0;
        }
    }
    cout << "Solution is " << count << endl;
}