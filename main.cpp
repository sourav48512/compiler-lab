#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> keywords = {"int", "main", "cout", "endl", "return", "using", "namespace", "include"};

bool isKeyword(string s) {
    for (const string& key : keywords) {
        if (s == key) return true;
    }
    return false;
}

int main() {
    ifstream file("bin\\Debug\\input.txt");

    if (!file) {
        cout << "Error: input.txt not found!" << endl;
        return 1;
    }

    cout << "=== File Content ===\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.clear();
    file.seekg(0);

    cout << "\n=== Tokens & Classification ===\n";
    char ch;
    string buffer;

    while (file.get(ch)) {
        string symbols = "(){};,<>=";
        if (symbols.find(ch) != string::npos) {
            if (!buffer.empty()) {
                if (isKeyword(buffer))
                    cout << buffer << " --> Keyword" << endl;
                else if (isdigit(buffer[0]))
                    cout << buffer << " --> Number" << endl;
                else
                    cout << buffer << " --> Identifier" << endl;
                buffer.clear();
            }
            cout << ch << " --> Symbol/Operator" << endl;
        }
        else if (isspace(ch)) {
            if (!buffer.empty()) {
                if (isKeyword(buffer))
                    cout << buffer << " --> Keyword" << endl;
                else if (isdigit(buffer[0]))
                    cout << buffer << " --> Number" << endl;
                else
                    cout << buffer << " --> Identifier" << endl;
                buffer.clear();
            }
        }
        else {
            buffer += ch;
        }
    }

    file.close();
    return 0;
}
