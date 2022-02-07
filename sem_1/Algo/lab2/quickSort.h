#include <iostream>
#include <fstream>

using namespace std;

vector<int> a;

int partition(int p, int r) {
    long x, i;
    x = a[r];
    i = p - 1;

    for (int j = p; j <= r - 1; j++) {
        if (a[j] <= x) {
            i = i + 1;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quicksort(int p, int r) {
    long q;
    if (p < r) {
        q = partition(p, r);
        quicksort(p, q - 1);
        quicksort(q + 1, r);
    }
}
int task_A() {

    ifstream fin(R"(C:\Users\mailo\CLionProjects\algoLab2\files\sort.in)");
    ofstream fout(R"(C:\Users\mailo\CLionProjects\algoLab2\files\sort.out)");
    int n;
    fin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }
    quicksort(a, 0, n - 1);

    for (int i : a) {
        fout << i << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}
