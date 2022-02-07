//
// Created by mailo on 08.10.2021.
//


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void generateArray(int n) {
    vector<int> a;
    a.resize(n);
    ofstream fout(R"(antiqs.out)");

    for(int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    for(int i = 0; i < n; i++) {
        swap(a[i],a[i/2]);
    }
    for(int &i: a) {
        fout << i << ' ';
    }
    fout.close();
}

void task_D() {
    ifstream fin(R"(antiqs.in)");
    int n;
    fin >> n;
    generateArray(n);
    fin.close();
}
