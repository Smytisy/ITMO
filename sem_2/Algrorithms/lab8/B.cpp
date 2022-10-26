//
// Created by mailo on 10.02.2022.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int B() {
    ifstream fin(R"(input.txt)");
    ofstream fout(R"(output.txt)");

    int n;
    fin >> n;
    vector<vector<int>> matrix;
    matrix.resize(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> matrix[i][j];
        }
    }
    bool flag = true;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                flag = false;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 1) {
            flag = false;
        }
    }
    if (flag) {
        fout << "YES";
    } else {
        fout << "NO";
    }

    fin.close();
    fout.close();
    return 0;
}

int main() {
    B();
    return 0;
}
