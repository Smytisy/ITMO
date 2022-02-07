//
// Created by mailo on 17.11.2021.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

bool check_tree(int root, vector<vector<int>> &tree, int min, int max) {
    if (min < tree[root][0] && max > tree[root][0]) {
        if (tree[root][1] == 0 && tree[root][2] == 0) {
            return true;
        }
        bool left = tree[root][1] == 0 || (check_tree(tree[root][1], tree, min, tree[root][0]));
        bool right = tree[root][2] == 0 || (check_tree(tree[root][2], tree, tree[root][0], max));
        return left && right;
    } else {
        return false;
    }
}



void task_B() {
    ifstream fin(R"(check.in)");
    ofstream fout(R"(check.out)");
    int n;
    fin >> n;
    if (n == 0) {
        fout << "YES";
        fin.close();
        fout.close();
        return;
    }
    vector<vector<int>> tree;
    tree.resize(n + 1);
    for (int i = 0; i < n; i++) {
        tree[i + 1].resize(3);
        fin >> tree[i + 1][0] >> tree[i + 1][1] >> tree[i + 1][2];
    }
    fout << (check_tree(1, tree, -2000000000, 2000000000) ? "YES" : "NO");

    fin.close();
    fout.close();
}
/*
int main() {
    task_B();
    return 0;
}
*/