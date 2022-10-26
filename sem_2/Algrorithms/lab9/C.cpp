//
// Created by mailo on 04.03.2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

int change_mark(int mark) {
    return mark == 1 ? 2 : 1;
}

void dfs(vector<vector<int>> &list, vector<int> &mark, int vertex, int color, bool& flag) {
    mark[vertex] = color;

    for (int v: list[vertex]) {
        if (mark[v] == 0) {
            dfs(list, mark, v, change_mark(color), flag);
        } else if (mark[v] == color) {
            flag = false;
            break;
        }
    }
}

int C() {
    ifstream fin(R"(bipartite.in)");
    ofstream fout(R"(bipartite.out)");
    int n, m, v1, v2;
    fin >> n >> m;
    n++;
    vector<vector<int>> list(n);
    for (int i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        list[v1].push_back(v2);
        list[v2].push_back((v1));
    }
    vector<int> mark(n);
    bool flag = true;
    for (int i = 1; i < n; ++i) {
        if(mark[i] == 0) {
            dfs(list, mark, i, 1, flag);
        }
    }
    if(flag) {
        fout << "YES" << endl;
    } else {
        fout << "NO" << endl;
    }

    fin.close();
    fout.close();
    return 0;
}

int main() {
    C();
    return 0;
}