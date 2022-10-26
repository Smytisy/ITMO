#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


void dfs(vector<vector<int>> &list, vector<int> &mark, int vertex, vector<int> &path, bool &flag, pair<int, int> &out_vertex) {
    mark[vertex] = true;

    for (auto &u: list[vertex]) {
        if (mark[u] == 0) {
            path[u] = vertex;
            dfs(list, mark, u, path, flag, out_vertex);
        }
        if (mark[u] == 1) {
            flag = true;
            out_vertex.second = vertex;
            out_vertex.first = u;
            break;
        }
    }
    mark[vertex] = 2;
}


int B() {
    ifstream fin(R"(cycle.in)");
    ofstream fout(R"(cycle.out)");
    int n, m, v1, v2;
    fin >> n >> m;
    n++;
    vector<vector<int>> list(n);
    vector<int> deg(n);
    for (int i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        list[v1].push_back(v2);
        ++deg[v2];
    }
    vector<int> path(n);
    vector<int> mark(n);
    bool flag = false;
    pair<int, int> out_vertex;
    for (int i = 1; i < n; ++i) {
        if (mark[i] == 0) {
            dfs(list, mark, i, path, flag, out_vertex);
        }
    }

    if (flag) {
        fout << "YES" << endl;
        vector<int> cycle;
        cycle.push_back(out_vertex.first);
        for(int vertex = out_vertex.second; vertex != out_vertex.first; vertex = path[vertex]) {
            cycle.push_back(vertex);
        }
        reverse(cycle.begin(), cycle.end());
        for(auto& vertex: cycle) {
            fout << vertex << ' ';
        }

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
};