//
// Created by mailo on 09.03.2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

void dfs(vector<vector<int>> &list, vector<int> &mark, int vertex, vector<int> &out) {
    mark[vertex] = 1;
    for (int v: list[vertex]) {
        if (mark[v] == 0) {
            dfs(list, mark, v, out);
        }
    }
    out.push_back(vertex);
}

bool check(vector<vector<int>> &list, vector<int> &out) {
    bool flag = true;
    int vertex = 0;
    for (int i = 0; i < out.size() - 1; i++) {
        flag = true;
        vertex = out[i];
        for(auto &v: list[vertex]) {
            if(v == out[i + 1]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return false;
        }
    }
    return true;
}

int E() {
    ifstream fin(R"(hamiltonian.in)");
    ofstream fout(R"(hamiltonian.out)");
    int n, m, v1, v2;
    fin >> n >> m;
    n++;
    vector<vector<int>> list(n);
    for (int i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        list[v1].push_back(v2);
    }
    vector<int> mark(n);
    vector<int> out;
    for(int i = 1; i < n; i++) {
        if(mark[i] == 0) {
            dfs(list, mark, i, out);
        }
    }
    reverse(out.begin(), out.end());
    if(check(list, out)) {
        fout << "YES";
    } else {
        fout << "NO";
    }

    fin.close();
    fout.close();
    return 0;
}

int main() {
    E();
    return 0;
}