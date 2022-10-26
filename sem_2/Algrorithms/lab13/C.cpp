#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> prefix_fun(const string &p) {
    vector<int> res(p.size());
    res[0] = 0;
    int j;
    for (int i = 1; i < p.size(); ++i) {
        j = res[i - 1];
        while (j > 0 && p[i] != p[j]) {
            j = res[j - 1];
        }
        if (p[i] == p[j]) {
            j++;
        }
        res[i] = j;
    }
    return res;
}


int C() {
    ifstream fin(R"(prefix.in)");
    ofstream fout(R"(prefix.out)");
    string p;
    fin >> p;
    vector<int> pref_v = prefix_fun(p);
    for(auto an: pref_v) {
        fout << an << ' ';
    }
    return 0;
}




int main() {
    C();

    return 0;
}