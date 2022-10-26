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


int D() {
    string p;
    int n;
    cin >> n;
    cin >> p;

    vector<int> pref_v = prefix_fun(p);
    vector<vector<int>> ans(p.size() + 1);
    for (int i = 0; i < p.size() + 1; ++i) {
        ans[i].resize(n);
        for (int j = 0; j < n; ++j) {
            char ch = (char) (97 + j);
            int out = 0;
            int i_tmp = i;
            if (i_tmp > 0 && ch != p[i_tmp]) {
                i_tmp = ans[pref_v[i_tmp - 1]][j];
                //cout << "kek:(" << i_tmp << ')';
            }
            out = i_tmp;
//            if (ch != p[i_tmp]) {
//                out = i_tmp;
//            } else {
//                out = i_tmp + 1;
//            }

            if (ch == p[i]) {
                out = i + 1;
            }

            cout << out << ' ';
            ans[i][j] = out;
        }
        cout << endl;
    }

    return 0;
}
int main() {
    D();
    return 0;
}