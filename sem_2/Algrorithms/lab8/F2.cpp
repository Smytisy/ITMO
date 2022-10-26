
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;



int F2() {
    ifstream fin(R"(input.txt)");
    ofstream fout(R"(output.txt)");
    int n, m;
    fin >> n >> m;
    pair<int, int> start, end;

    vector<vector<char>> lab (n, vector<char> (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fin >> lab[i][j];
            if (lab[i][j] == 'S') {
                start.first = i;
                start.second = j;
            }
            if (lab[i][j] == 'T') {
                end.first = i;
                end.second = j;
            }
        }
    }

    queue<pair<int, int>> q;
    q.push(start);

    vector<vector<vector<char>>> path (n, vector<vector<char>> (m));

    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        if (cur.first == end.first && cur.second == end.second) {
            // return
            break;
        }
        //[cur.first][cur.second]
        if (cur.first - 1 >= 0 && lab[cur.first - 1][cur.second] != '#' && path[cur.first - 1][cur.second].empty()) {
            // up
            pair<int, int> tmp;
            tmp.first = cur.first - 1;
            tmp.second = cur.second;

            q.push(tmp);

            path[cur.first - 1][cur.second] = path[cur.first][cur.second];
            path[cur.first - 1][cur.second].push_back('U');
        }
        if (cur.first + 1 < n && lab[cur.first + 1][cur.second] != '#' && path[cur.first + 1][cur.second].empty()) {
            // down
            pair<int, int> tmp;
            tmp.first = cur.first + 1;
            tmp.second = cur.second;

            q.push(tmp);

            path[cur.first + 1][cur.second] = path[cur.first][cur.second];
            path[cur.first + 1][cur.second].push_back('D');
        }
        if (cur.second - 1 >= 0 && lab[cur.first][cur.second - 1] != '#' && path[cur.first][cur.second - 1].empty()) {
            // left
            pair<int, int> tmp;
            tmp.first = cur.first;
            tmp.second = cur.second - 1;

            q.push(tmp);

            path[cur.first][cur.second - 1] = path[cur.first][cur.second];
            path[cur.first][cur.second - 1].push_back('L');
        }
        if (cur.second + 1 < m && lab[cur.first][cur.second + 1] != '#' && path[cur.first][cur.second + 1].empty()) {
            // right
            pair<int, int> tmp;
            tmp.first = cur.first;
            tmp.second = cur.second + 1;

            q.push(tmp);

            path[cur.first][cur.second + 1] = path[cur.first][cur.second];
            path[cur.first][cur.second + 1].push_back('R');
        }
    }

//    cout << end.first << ' ' << end.second << endl;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            cout << endl;
//            cout << i << j << ' ';
//            for (char k: path[i][j]) {
//                cout << k;
//            }
//        }
//    }

    if (path[end.first][end.second].empty()) {
        fout << -1;
    } else {
        fout << path[end.first][end.second].size() << endl;
        for (char i: path[end.first][end.second]) {
            fout << i;
        }
    }


    return 0;
}

int main() {
    F2();
    return 0;
}
