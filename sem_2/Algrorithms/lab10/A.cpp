

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

const int INF = 10000000;

struct Edge {
    int _to;
    int _weight;
};

int A() {
    ifstream fin(R"(input.txt)");
    ofstream fout(R"(output.txt)");
    int n, m;
    fin >> n >> m;
    n++;
    vector<vector<int> > g(n);
    int a, b;
    for (int i = 0; i < m; ++i) {
        fin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 1; i < n; ++i) {
        int deg = 0;
        for (int vertex: g[i]) {
            ++deg;
        }
        fout << deg << ' ';
    }
    fin.close();
    fout.close();
    return 0;
}

int main() {
    A();
    return 0;
}