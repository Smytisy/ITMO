//
// Created by mailo on 09.03.2022.
//
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

void dfs(vector<vector<int>> &list, vector<int> &mark, int vertex) {
    for (int v: list[vertex]) {
        if (mark[v] == -1) {
            dfs(list, mark, v);
        }
    }
    for (auto &v: list[vertex]) {
        mark[vertex] = max(mark[vertex], (mark[v] + 1) % 2);
    }
    if (mark[vertex] == -1) {
        mark[vertex] = 0;
    }
}


int F() {
    ifstream fin(R"(game.in)");
    ofstream fout(R"(game.out)");
    int n, m, s, v1, v2;
    fin >> n >> m >> s;
    n++;
    vector<vector<int>> list(n);
    for (int i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        list[v1].push_back(v2);
    }
    vector<int> mark(n, -1);
    dfs(list, mark, s);

    if(mark[s] == 1) {
        fout << "First player wins" << endl;
    } else {
        fout << "Second player wins" << endl;
    }

    fin.close();
    fout.close();
    return 0;
}

int main() {
    F();
    return 0;
}
