#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> array;

int find_border_right(int x) {
    int l = -1;
    int r = array.size() - 1;
    while (r > l + 1) {
        int m = (l + r) / 2;
        if (array[m] >= x) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

int find_border_left(int x) {
    int l = -1;
    int r = array.size() - 1;
    while (r > l + 1) {
        int m = (l + r) / 2;
        if (array[m] > x) {
            r = m;
        } else {
            l = m;
        }
    }
    return l;
}


void task_E() {
    ifstream fin(R"(binsearch.in)");
    ofstream fout(R"(binsearch.out)");
    int n, m;
    fin >> n;
    array.resize(n + 1);
    for (int i = 0; i < n; i++) {
        fin >> array[i];
    }
    fin >> m;
    int a;
    for (int i = 0; i < m; i++) {
        fin >> a;
        int r = find_border_right(a);
        int l = find_border_left(a);
        if (array[r] == array[l]) {
            fout << r + 1 << ' ' << l + 1 << endl;
        } else {
            fout << -1 << ' ' << -1 << endl;
        }
    }

    fin.close();
    fout.close();
}

int main() {
    task_E();
    return 0;
}
