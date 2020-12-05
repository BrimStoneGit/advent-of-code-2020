#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

enum enum_fields {BYR = 0, IYR = 1, EYR = 2, HGT = 3, HCL = 4, ECL = 5, PID = 6, CID = 7};

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
    parsed_vec.push_back("");
    return parsed_vec;
}

int map_field_to_int(string given_field) {
    if (given_field == "byr") {
        return BYR;
    }
    else if (given_field == "iyr") {
        return IYR;
    }
    else if (given_field == "eyr") {
        return EYR;
    }
    else if (given_field == "hgt") {
        return HGT;
    }
    else if (given_field == "hcl") {
        return HCL;
    }
    else if (given_field == "ecl") {
        return ECL;
    }
    else if (given_field == "pid") {
        return PID;
    }
    else if (given_field == "cid") {
        return CID;
    }
    return 8;
}

int main() {
    std::vector<string> vec_passport;
    vec_passport = readFile("input.txt");
    string eye_colors_array[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    std::vector<string> eye_colors (eye_colors_array, eye_colors_array + sizeof(eye_colors_array) / sizeof(string));

    int count = 0;

    uint8_t result = 0x00;
    // result = result | 0xF0;
    // result = result | 0x0F;
    // printf("result is currently %x\n", result);
    // Bits are representing validity of:
    // byr, iyr, eyr, hgt, hcl, ecl, pid, cid
    // so only 0xFE or 0xFF would be valid



    for (int i = 0; i < vec_passport.size(); i++) {
        string identifier = vec_passport[i].substr(0, vec_passport[i].find(":"));
        string value = vec_passport[i].substr(vec_passport[i].find(":") + 1, vec_passport[i].size());
        switch (map_field_to_int(identifier)) {
            case BYR:
                if (stoi(value) >= 1920 && stoi(value) <= 2002) {
                    result = result | 0x80;
                }
                break;
            case IYR:
                if (stoi(value) >= 2010 && stoi(value) <= 2020) {
                    result = result | 0x40;
                }
                break;
            case EYR:
                if (stoi(value) >= 2020 && stoi(value) <= 2030) {
                    result = result | 0x20;
                }
                break;
            case HGT:
                if (value.find("cm") == string::npos && stoi(value.substr(0, value.find("in"))) >= 59 && stoi(value.substr(0, value.find("in"))) <= 76 ||
                value.find("in") == string::npos && stoi(value.substr(0, value.find("cm"))) >= 150 && stoi(value.substr(0, value.find("cm"))) <= 193) {
                    result = result | 0x10;
                }
                break;
            case HCL:
                if (value.size() == 7 && value.at(0) == '#' && stoi(value.substr(1, value.size()), 0, 16) >= 0 && stoi(value.substr(1, value.size()), 0, 16) <= 16777215) {
                    result = result | 0x08;
                }
                break;
            case ECL:
                for (int j = 0; j < eye_colors.size(); j++) {
                    if (value == eye_colors[j]) {
                        result = result | 0x04;
                        break;
                    }
                }
                break;
            case PID:
                if (value.size() == 9) {
                    try
                    {
                        int conv_number = std::stoi(value);
                        result = result | 0x02;
                    }
                    catch(const std::invalid_argument& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                break;
            case CID:
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