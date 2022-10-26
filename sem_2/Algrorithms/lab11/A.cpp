#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long long INF = 1000000000000000;

int A() {
    ifstream fin(R"(pathmgep.in)");
    ofstream fout(R"(pathmgep.out)");

    long long n, start, finish;
    fin >> n >> start >> finish;
    --start;
    --finish;


    long long a;
    vector<vector<pair<int, long long >>> edj_matrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> a;
            if (a > -1) {
                edj_matrix[i].push_back(make_pair(j, a));
            }
        }
    }

    vector<long long> dist(n, INF);
    vector<int> visited(n, 0);

    dist[start] = 0;
    long long current;

    for (int j = 0; j < n; ++j) {
        current = -1;
        // find current
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (current == -1 || dist[current] > dist[i])) {
                current = i;
            }
        }
        if (dist[current] == INF) {
            break;
        }
        
        // set distance
        visited[current] = 1;
        for (pair<int, long long> vertex: edj_matrix[current]) {
            dist[vertex.first] = min(dist[current] + vertex.second, dist[vertex.first]);

        }

    }

    if (dist[finish] != INF) {
        fout << dist[finish];
    } else fout << -1;

    fin.close();
    fout.close();
    return 0;
}

int main() {
    return A();
}