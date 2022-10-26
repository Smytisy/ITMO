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


int B() {
    ifstream fin(R"(search2.in)");
    ofstream fout(R"(search2.out)");
    string p, t;
    fin >> p;
    fin >> t;
    
    vector<int> pref_v = prefix_fun(p);
    vector<int> ans;

    int j = 0;
    int i = 0;

    while (i < t.size()) {
        if (p[j] == t[i]) {
            i++;
            j++;
        }

        if (j == p.size()) {
            ans.push_back(i - j + 1);
            j = pref_v[j - 1];
        } else if (i < t.size() && p[j] != t[i]) {
            if (j != 0) {
                j = pref_v[j - 1];
            } else {
                ++i;
            }
        }
    }


    fout << ans.size() << endl;
    for (auto an: ans) {
        fout << an << ' ';
    }

    return 0;
}

int main() {
    B();

    return 0;
}