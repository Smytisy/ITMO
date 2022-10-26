#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

//void dfs(vector<vector<int>> &list, vector<bool> &mark, int vertex, queue<int> &sort_out) {
//    mark[vertex] = true;
//    for(auto& u: list[vertex]) {
//        if(!mark[u]) {
//            dfs(list, mark, u, sort_out);
//        }
//    }
//    sort_out.push(vertex);
//}

void topSort(vector<vector<int>> &list, vector<int> &deg, queue<int> &sort_out) {
    stack<int> z;
    for (int i = 1; i < deg.size(); ++i) {
        if (deg[i] == 0) {
            z.push(i);
        }
    }
    int v1;
    while (!z.empty()) {
        v1 = z.top();
        sort_out.push(v1);
        z.pop();
        for (auto &vertex: list[v1]) {
            --deg[vertex];
            if (deg[vertex] == 0) {
                z.push(vertex);
            }
        }
    }
}

int A() {
    ifstream fin(R"(topsort.in)");
    ofstream fout(R"(topsort.out)");
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
    queue<int> sort_out;
    topSort(list, deg, sort_out);

    if (sort_out.size() < n - 1) {
        fout << -1;
    } else {
        while (!sort_out.empty()) {
            fout << sort_out.front() << ' ';
            sort_out.pop();
        }
    }

    fin.close();
    fout.close();
    return 0;
}

int main() {
    A();
    return 0;
};