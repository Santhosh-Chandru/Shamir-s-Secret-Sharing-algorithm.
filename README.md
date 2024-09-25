//Shamir-s-Secret-Sharing-algorithm.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <nlohmann/json.hpp>  // Include the JSON library

using json = nlohmann::json;

// Function to decode the value from the given base
long long decodeValue(const std::string& value, int base) {
    return std::stoll(value, nullptr, base);
}

// Function to perform Lagrange Interpolation
double lagrangeInterpolation(const std::vector<int>& x, const std::vector<long long>& y, int n) {
    double result = 0;

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (0.0 - x[j]) / static_cast<double>(x[i] - x[j]);  // f(0) for constant term
            }
        }
        result += term;
    }

    return result;
}

int main() {
    // Read the JSON file
    std::ifstream input_file("input.json");
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open input file!" << std::endl;
        return 1;
    }

    // Parse the JSON file
    json data;
    input_file >> data;

    // First test case data
    int n1 = data["keys"]["n"];
    int k1 = data["keys"]["k"];

    std::vector<int> x1;
    std::vector<long long> y1;

    for (int i = 1; i <= n1; ++i) {
        std::string key = std::to_string(i);
        if (data.contains(key)) {
            int base = std::stoi(data[key]["base"].get<std::string>());
            std::string value = data[key]["value"];
            x1.push_back(i);  // The x-coordinate (key)
            y1.push_back(decodeValue(value, base));  // The y-coordinate (decoded value)
        }
    }

    // Perform Lagrange Interpolation for the first test case
    double c1 = lagrangeInterpolation(x1, y1, k1);

    // Output the result
    std::cout << "The constant term (c) for the first test case is: " << c1 << std::endl;

    return 0;
}
// input.json
Sample test case1
{
    "keys": {
        "n": 4,
        "k": 3
    },
    "1": {
        "base": "10",
        "value": "4"
    },
    "2": {
        "base": "2",
        "value": "111"
    },
    "3": {
        "base": "10",
        "value": "12"
    },
    "6": {
        "base": "4",
        "value": "213"
    }
}
Sample test case2
{
    "keys": {
        "n": 9,
        "k": 6
    },
    "1": {
        "base": "10",
        "value": "28735619723837"
    },
    "2": {
        "base": "16",
        "value": "1A228867F0CA"
    },
    "3": {
        "base": "12",
        "value": "32811A4AA0B7B"
    },
    "4": {
        "base": "11",
        "value": "917978721331A"
    },
    "5": {
        "base": "16",
        "value": "1A22886782E1"
    },
    "6": {
        "base": "10",
        "value": "28735619654702"
    },
    "7": {
        "base": "14",
        "value": "71AB5070CC4B"
    },
    "8": {
        "base": "9",
        "value": "122662581541670"
    },
    "9": {
        "base": "8",
        "value": "642121030037605"
    }
}


//code withuot reading from the json file
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// Function to decode the value from the given base
long long decodeValue(const char *value, int base) {
    return strtoll(value, nullptr, base);
}

// Function to perform Lagrange Interpolation
double lagrangeInterpolation(int x[], long long y[], int n) {
    double result = 0;

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (0 - x[j]) / (double)(x[i] - x[j]);  // f(0) for constant term
            }
        }
        result += term;
    }

    return result;
}

int main() {
    // First test case data
    int n1 = 4;
    int k1 = 3;
    int x1[] = {1, 2, 3, 6};  // The keys
    long long y1[] = {
        decodeValue("4", 10),    // y1 decoded from base 10
        decodeValue("111", 2),   // y2 decoded from base 2
        decodeValue("12", 10),   // y3 decoded from base 10
        decodeValue("213", 4)    // y6 decoded from base 4
    };

    // Second test case data
    int n2 = 9;
    int k2 = 6;
    int x2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};  // The keys
    long long y2[] = {
        decodeValue("28735619723837", 10),  // y1 decoded from base 10
        decodeValue("1A228867F0CA", 16),   // y2 decoded from base 16
        decodeValue("32811A4AA0B7B", 12),  // y3 decoded from base 12
        decodeValue("917978721331A", 11),  // y4 decoded from base 11
        decodeValue("1A22886782E1", 16),   // y5 decoded from base 16
        decodeValue("28735619654702", 10), // y6 decoded from base 10
        decodeValue("71AB5070CC4B", 14),   // y7 decoded from base 14
        decodeValue("122662581541670", 9), // y8 decoded from base 9
        decodeValue("642121030037605", 8)  // y9 decoded from base 8
    };

    // Finding the constant term (c) for both test cases using Lagrange Interpolation
    double c1 = lagrangeInterpolation(x1, y1, k1);
    double c2 = lagrangeInterpolation(x2, y2, k2);

    // Output the results
    cout << "The constant term (c) for the first test case is: " << c1 << endl;
    cout << "The constant term (c) for the second test case is: " << c2 << endl;

    return 0;
}
