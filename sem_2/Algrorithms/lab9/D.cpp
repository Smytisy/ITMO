#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

void dfs1(vector<vector<int>> &list, vector<int> &mark, int vertex, vector<int> &pusher) {
    mark[vertex] = 1;
    for (auto &ver: list[vertex]) {
        if (mark[ver] == 0) {
            dfs1(list, mark, ver, pusher);
        }
    }
    pusher.push_back(vertex);
}

void dfs2(vector<vector<int>> &list, vector<int> &mark, int vertex, vector<int> &components) {
    mark[vertex] = 1;
    components.push_back(vertex);
    for (auto &ver: list[vertex]) {
        if (mark[ver] == 0) {
            dfs1(list, mark, ver, components);
        }
    }
}
int D() {
    ifstream fin(R"(cond.in)");
    ofstream fout(R"(cond.out)");
    int n, m, v1, v2;
    fin >> n >> m;
    n++;
    vector<vector<int>> list1(n);
    vector<vector<int>> list2(n);

    for (int i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        list1[v1].push_back(v2);
        list2[v2].push_back((v1));
    }
    vector<int> mark(n);
    vector<int> pusher, components;
    for (int i = 1; i < n; ++i) {
        if (mark[i] == 0) {
            dfs1(list1, mark, i, pusher);
        }
    }
    mark.assign(n, 0);
    reverse(pusher.begin(), pusher.end());
    for (auto &ver: pusher) {
    }
    int k = 0;
    vector <int> out (n);
    for(auto &element: pusher) {
        if(mark[element] == 0) {
            dfs2(list2, mark, element, components);

            ++k;
            for (auto &ver: components) {
                out[ver] = k;
            }

            components.clear();
        }
    }
    fout << k << endl;
    for(int i = 1; i < n; i++) {
        fout << out[i] << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}

int main() {
    D();
    return 0;
}