//
// Created by mailo on 11.02.2022.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void dfs(vector<vector<int>> &list, vector<int> &components, int vertex, int number_component) {
    components[vertex] = number_component;
    for (int i = 0; i < list[vertex].size(); i++) {
        if (components[list[vertex][i]] == 0) {
            dfs(list, components, list[vertex][i], number_component);
        }
    }
}

int D() {
    ifstream fin(R"(components.in)");
    ofstream fout(R"(components.out)");
    int n, m, v1, v2;
    fin >> n >> m;
    n++;
    vector<vector<int>> edgeList(n);
    for (int i = 0; i < m; i++) {
        fin >> v1 >> v2;
        edgeList[v1].push_back(v2);
        edgeList[v2].push_back(v1);
    }
    vector<int> components(n);
    int number_components = 0;
    for (int i = 1; i < n; i++) {
        if (components[i] == 0) {
            number_components++;
            dfs(edgeList, components, i, number_components);
        }
    }
    fout << number_components << endl;
    for (int i = 1; i < n; i++) {
        fout << components[i] << ' ';
    }
    return 0;
}

int main() {
    D();
    return 0;
}