#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void write_csv(const string& filename, const vector<vector<string>>& data) {
    ofstream file(filename);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}

int main() {
    vector<vector<string>> data = {
        {"Name", "Age", "City"},
        {"Alice", "30", "New York"},
        {"Bob", "25", "Los Angeles"}
    };
    write_csv("example.csv", data);
    return 0;
}