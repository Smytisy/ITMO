//
// Created by mailo on 10.02.2022.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int A() {
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

    for (int i = 0; i < m; i++) {
        fin >> a >> b;
        matrix[a][b]++;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            fout << matrix[i][j] << ' ';
        }
        fout << endl;
    }
    fin.close();
    fout.close();
    return 0;
}

int main() {
    A();
    return 0;
}
