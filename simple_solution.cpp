// #include <iostream>
// #include <fstream>
// #include <string>
// #include <vector>
// #include <cmath>
// #include <sstream>
// #include <map>

// using namespace std;

// // Simple JSON parser for our specific format
// map<string, map<string, string>> parseJSON(const string& filename) {
//     map<string, map<string, string>> data;
//     ifstream file(filename);
//     string line;
//     string currentKey = "";
    
//     while (getline(file, line)) {
//         // Remove spaces and quotes
//         string clean = "";
//         for (char c : line) {
//             if (c != ' ' && c != '\t' && c != '"') clean += c;
//         }
        
//         // Parse key-value pairs
//         if (clean.find(":") != string::npos && clean.find("{") == string::npos) {
//             size_t colon = clean.find(":");
//             string key = clean.substr(0, colon);
//             string value = clean.substr(colon + 1);
            
//             // Remove commas
//             if (value.back() == ',') value.pop_back();
            
//             if (currentKey == "keys") {
//                 data["keys"][key] = value;
//             } else if (currentKey != "") {
//                 data[currentKey][key] = value;
//             }
//         } else if (clean.find(":") != string::npos && clean.find("{") != string::npos) {
//             size_t colon = clean.find(":");
//             currentKey = clean.substr(0, colon);
//         }
//     }
    
//     return data;
// }

// // Convert baseN string to decimal
// long long baseN_to_decimal(const string& value, int base) {
//     long long result = 0;
//     for (char c : value) {
//         int digit = 0;
//         if (c >= '0' && c <= '9') {
//             digit = c - '0';
//         } else if (c >= 'A' && c <= 'Z') {
//             digit = c - 'A' + 10;
//         } else if (c >= 'a' && c <= 'z') {
//             digit = c - 'a' + 10;
//         }
        
//         if (digit >= base) {
//             throw invalid_argument("Invalid digit for given base");
//         }
        
//         result = result * base + digit;
//     }
//     return result;
// }

// // Lagrange interpolation to find the secret (P(0))
// double lagrange_interpolation(const vector<pair<int, long long>>& points) {
//     double result = 0.0;
//     int n = points.size();
    
//     for (int i = 0; i < n; i++) {
//         double basis = 1.0;
        
//         for (int j = 0; j < n; j++) {
//             if (i != j) {
//                 basis *= (0.0 - points[j].first) / (points[i].first - points[j].first);
//             }
//         }
        
//         result += points[i].second * basis;
//     }
    
//     return result;
// }

// int main() {
//     cout << "Starting Shamir's Secret Sharing Solver..." << endl;
    
//     // Manual data input (avoiding JSON parsing issues)
//     vector<pair<int, long long>> points;
    
//     // Data from your test case
//     points.push_back({1, 4});   // Base 10: "4" = 4
//     points.push_back({2, 7});   // Base 2: "111" = 7
//     points.push_back({3, 12});  // Base 10: "12" = 12
//     points.push_back({6, 39});  // Base 4: "213" = 39
    
//     int n = 4;
//     int k = 3;
    
//     cout << "=== Shamir's Secret Sharing Solver ===" << endl;
//     cout << "n (total shares) = " << n << endl;
//     cout << "k (minimum needed) = " << k << endl;
//     cout << "Polynomial degree = " << (k-1) << endl << endl;
    
//     cout << "Data points:" << endl;
//     for (const auto& point : points) {
//         cout << "(" << point.first << ", " << point.second << ")" << endl;
//     }
    
//     // Use first k points for interpolation
//     if (points.size() > k) {
//         points.resize(k);
//         cout << "\nUsing first " << k << " points for interpolation." << endl;
//     }
    
//     double secret = lagrange_interpolation(points);
    
//     cout << "\n=== RESULT ===" << endl;
//     cout << "The secret (constant term C) = " << (long long)round(secret) << endl;
//     cout << "\n✓ Program executed successfully!" << endl;
    
//     return 0;
// }

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
#include<bits/stdc++.h>

using namespace std;

// Enhanced baseN to decimal converter for large numbers
long long baseN_to_decimal(const string& value, int base) {
    long long result = 0;
    for (char c : value) {
        int digit = 0;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        }
        
        if (digit >= base) {
            throw invalid_argument("Invalid digit for given base");
        }
        
        result = result * base + digit;
    }
    return result;
}

// Simple JSON parser for our format
map<string, map<string, string>> parseJSON(const string& filename) {
    map<string, map<string, string>> data;
    ifstream file(filename);
    string line;
    string currentKey = "";
    
    while (getline(file, line)) {
        // Remove spaces, tabs, and quotes
        string clean = "";
        for (char c : line) {
            if (c != ' ' && c != '\t' && c != '"') clean += c;
        }
        
        if (clean.find(":") != string::npos && clean.find("{") == string::npos) {
            size_t colon = clean.find(":");
            string key = clean.substr(0, colon);
            string value = clean.substr(colon + 1);
            
            // Remove commas
            if (!value.empty() && value.back() == ',') value.pop_back();
            
            if (currentKey == "keys") {
                data["keys"][key] = value;
            } else if (!currentKey.empty()) {
                data[currentKey][key] = value;
            }
        } else if (clean.find(":") != string::npos && clean.find("{") != string::npos) {
            size_t colon = clean.find(":");
            currentKey = clean.substr(0, colon);
        }
    }
    
    return data;
}

double lagrange_interpolation(const vector<pair<int, long long>>& points) {
    double result = 0.0;
    int n = points.size();
    
    for (int i = 0; i < n; i++) {
        double basis = 1.0;
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                basis *= (0.0 - points[j].first) / (points[i].first - points[j].first);
            }
        }
        
        result += points[i].second * basis;
    }
    
    return result;
}

int main() {
    cout << "=== Shamir's Secret Sharing Solver ===" << endl;
    
    // Read from JSON file
    auto data = parseJSON("test.json");
    
    int n = stoi(data["keys"]["n"]);
    int k = stoi(data["keys"]["k"]);
    
    cout << "n (total shares) = " << n << endl;
    cout << "k (minimum needed) = " << k << endl;
    cout << "Polynomial degree = " << (k-1) << endl << endl;
    
    vector<pair<int, long long>> points;
    
    cout << "Converting shares from different bases:" << endl;
    for (auto& item : data) {
        if (item.first == "keys") continue;
        
        int x = stoi(item.first);
        int base = stoi(item.second["base"]);
        string value_str = item.second["value"];
        
        long long y = baseN_to_decimal(value_str, base);
        
        points.push_back({x, y});
        cout << "Share " << x << ": Base " << base << " value '" << value_str 
             << "' -> Decimal " << y << endl;
    }
    
    // Sort points and use first k
    sort(points.begin(), points.end());
    if (points.size() > k) {
        points.resize(k);
    }
    
    cout << "\nUsing first " << k << " points for interpolation." << endl;
    
    double secret = lagrange_interpolation(points);
    
    cout << "\n=== RESULT ===" << endl;
    cout << "The secret (constant term C) = " << (long long)round(secret) << endl;
    cout << "\nProgram executed successfully!" << endl;
    
    return 0;
}
