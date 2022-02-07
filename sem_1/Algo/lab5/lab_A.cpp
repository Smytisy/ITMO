//
// Created by mailo on 17.11.2021.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int get_height(int root, vector<vector<int>> & tree) {
    if (tree[root][1] == 0 && tree[root][2] == 0) {
        return 1;
    }
    int left = tree[root][1] != 0 ? get_height(tree[root][1], tree) : 1;
    int right = tree[root][2] != 0 ? get_height(tree[root][2], tree) : 1;
    return left > right ? left + 1 : right + 1;
}


void task_A() {
    ifstream fin(R"(height.in)");
    ofstream fout(R"(height.out)");
    int n;
    fin >> n;
    vector<vector<int>> tree;
    if (n == 0) {
        fout << 0;
        fin.close();
        fout.close();
        return;
    }
    tree.resize(n + 1);
    for(int i = 0; i < n; i++) {
        tree[i + 1].resize(3);
        fin >> tree[i + 1][0] >> tree[i + 1][1] >> tree[i + 1][2];
    }
    fout << get_height(1, tree);

    fin.close();
    fout.close();
}
/*
int main() {
    task_A();
    return 0;
}
*/


