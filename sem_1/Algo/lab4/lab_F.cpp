#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


double find(double h1, int n) {
    double l, r;
    double B;
    l = 0;
    r = h1;
    B = -1;

    while ((r - l) > 0.00000001) {
        double m = (l + r) / 2;
        double prev = h1;
        double cur = m;

        bool underGround = cur > 0;
        for (int i = 2; i < n; i++) {
            double next = 2 * cur - prev + 2;
            underGround &= next > 0;

            prev = cur;
            cur = next;
        }
        if (underGround) {
            r = m;
            B = cur;
        } else {
            l = m;
        }
    }
    return B;
}


void task_F() {
    ifstream fin(R"(garland.in)");
    ofstream fout(R"(garland.out)");
    int n;
    double A;
    fin >> n >> A;
    fout << setprecision(2) << fixed << find(A, n);

    fin.close();
    fout.close();
}
/*
int main() {
    task_F();
    return 0;
}
*/