//
// Created by mailo on 22.10.2021.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



void task_A() {
    ifstream fin(R"(isheap.in)");
    ofstream fout(R"(isheap.out)");
    int n;
    fin >> n;
    vector<int> array_heap;
    array_heap.resize(n + 1);
    for (int i = 1; i < n + 1; i++) {
        fin >> array_heap[i];
    }
    bool flag = true;
    n = array_heap.size();
    for (int i = 1; i < n; ++i) {
        if (2 * i < n && array_heap[i] > array_heap[2 * i]) {
            flag = false;
            break;
        }
        if (2 * i + 1 < n && array_heap[i] > array_heap[2 * i + 1]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        fout << "YES";
    } else {
        fout << "NO";
    }
    fin.close();
    fout.close();

}
