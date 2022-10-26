//
// Created by mailo on 11.02.2022.
//

//
// Created by mailo on 11.02.2022.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;


int E() {
    ifstream fin(R"(pathbge1.in)");
    ofstream fout(R"(pathbge1.out)");
    int n, m, v1, v2;
    fin >> n >> m;
    n++;
    vector<vector<int>> edgeList(n);
    for (int i = 0; i < m; i++) {
        fin >> v1 >> v2;
        edgeList[v1].push_back(v2);
        edgeList[v2].push_back(v1);
    }

    queue<int> q;
    q.push(1);
    vector<bool> used (n);
    vector<int> deep (n);
    used[1] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < edgeList[v].size(); i++) {
            int to = edgeList[v][i];
            if (!used[to]) {
                used[to] = true;
                q.push(to);
                deep[to] = deep[v] + 1;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        fout << deep[i] << ' ';
    }
    return 0;
}

int main() {
    E();
    return 0;
}