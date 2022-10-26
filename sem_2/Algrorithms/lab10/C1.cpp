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
#include <set>

using namespace std;

const int INF = 10000000;

struct Edge {
    int _to;
    int _weight;
};

int C1() {
    ifstream fin(R"(spantree3.in)");
    ofstream fout(R"(spantree3.out)");
    int n, m;
    fin >> n >> m;
    vector<vector<Edge> > g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        fin >> a >> b >> w;
        a--;
        b--;
        g[a].push_back(Edge{b, w});
        g[b].push_back(Edge{a, w});
    }
    vector<int> min_edge(n);
    vector<int> end_edge(n);
    for(int i = 0; i < n; i++) {
        min_edge[i] = INF;
        end_edge[i] = -1;
    }
    min_edge[0] = 0;
    multiset<pair<int, int> > q;
    q.insert(make_pair(0, 0));
    long long sum = 0;
    set<int> A;
    A.insert(0);
    for (int i = 0; i < n; ++i) {
        int v = q.begin()->second;
        q.erase(q.begin());
        A.insert(v);
        if (end_edge[v] != -1) {
            //cout << v << ' ' << end_edge[v] << endl;
            sum += min_edge[v];
        }
        for (size_t j = 0; j < g[v].size(); ++j) {
            int to = g[v][j]._to;
            int weight = g[v][j]._weight;

            if (A.find(to) == A.end()) {
                if (weight < min_edge[to]) {
                    q.erase(make_pair(min_edge[to], to));
                    min_edge[to] = weight;
                    end_edge[to] = v;
                    q.insert(make_pair(min_edge[to], to));
                }
            }
        }
    }
    fout << sum << endl;

    fin.close();
    fout.close();
    return 0;
}

int main() {
    C1();
    return 0;
}
