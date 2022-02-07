//
// Created by mailo on 08.10.2021.
//


#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

unsigned long long counter;

vector<int> merge(vector<int> a, vector<int> b) {
    vector<int> c;
    c.resize(a.size() + b.size());
    int i = 0, j = 0;
    while (i < a.size() || j < b.size()) {
        if (j == b.size() || i < a.size() && a[i] <= b[j]) {
            c[i + j] = a[i];
            i++;
        } else {
            c[i + j] = b[j];
            counter = counter + a.size() - i;
            j++;
        }
    }
    return c;
}

vector<int> firstHalf(vector<int> a) {
    vector<int> l;
    l.resize(a.size() / 2);
    for (int i = 0; i < a.size() / 2; i++) {
        l[i] = a[i];
    }
    return l;
}

vector<int> secondHalf(vector<int> a) {
    vector<int> r;
    r.resize(a.size() - a.size() / 2);
    for (int i = a.size() / 2; i < a.size(); i++) {
        r[i - a.size() / 2] = a[i];
    }
    return r;
}


vector<int> sort(vector<int> a) {
    int n = a.size();
    if (n <= 1) {
        return a;
    }

    vector<int> l = firstHalf(a);
    vector<int> r = secondHalf(a);

    l = sort(l);
    r = sort(r);

    return merge(l, r);
}

void task_C() {
    ifstream fin(R"(C:\Users\mailo\CLionProjects\algoLab2\files\inversions.in)");
    ofstream fout(R"(C:\Users\mailo\CLionProjects\algoLab2\files\inversions.out)");
    int n;
    fin >> n;
    vector<int> a;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }
    a = sort(a);
    fout << counter;

    fin.close();
    fout.close();
}