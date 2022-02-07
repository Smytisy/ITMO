//
// Created by mailo on 12.12.2021.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    vector<int> in;
    in.resize(8);
    for (int i = 0; i < 1000; i++) {
        in[i * i % 8] += 1;
    }

    for( int i = 0; i < 8; i++) {
        cout << i << " count: " <<in[i] << endl;
    }
    return 0;
}