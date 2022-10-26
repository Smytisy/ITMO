#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin(R"(search1.in)");
    ofstream fout(R"(search1.out)");
    string p, t;
    fin >> p;
    fin >> t;

    vector<int> ans;
    for (int i = 0; i < t.size(); ++i) {
        bool flag = false;
        for (int j = 0; j < p.size(); ++j) {
            if (t[i + j] == p[j]) {
                flag = true;
            } else {
                flag = false;
                break;
            }
        }
        if (flag) {
            ans.push_back(i + 1);
        }
    }
    fout << ans.size() << endl;
    for (int an : ans) {
        fout << an << ' ';
    }
    return 0;
}
