//
// Created by mailo on 11.02.2022.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int C() {
    ifstream fin(R"(input.txt)");
    ofstream fout(R"(output.txt)");
    int n, m, a, b;
    fin >> n >> m;
    n++;
    vector<vector<int>> matrix;
    matrix.resize(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(n);
    }
    bool flag = false;
    for (int i = 0; i < m; i++) {
        fin >> a >> b;
        matrix[a][b]++;
        if (matrix[a][b] >= 2 || matrix[b][a] >= 1) {
            flag = true;
        }
    }
    if (flag) {
        fout << "YES";
    } else {
        fout << "NO";
    }
    return 0;
}

int main() {
    C();
    return 0;
}
