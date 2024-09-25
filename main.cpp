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
