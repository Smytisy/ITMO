#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <valarray>
#include <iomanip>


using namespace std;

const double INF = 10000000;


struct Point {
    int x;
    int y;
};

double getWeight(Point const &p1, Point const &p2) {
    return sqrt(abs(p1.x - p2.x) * abs(p1.x - p2.x) + abs(p1.y - p2.y) * abs(p1.y - p2.y));
}

int B() {
    ifstream fin(R"(spantree.in)");
    ofstream fout(R"(spantree.out)");
    int n;
    fin >> n;
    vector<Point> plane(n);
    int a, b;
    for (int i = 0; i < n; ++i) {
        fin >> a >> b;
        plane[i].x = a;
        plane[i].y = b;
    }

    vector<double> edges(n, INF);
    vector<int> visited(n);
    int current = 0;
    int next = 0;
    double res = 0;

    for (int i = 1; i < n; ++i) {
        double minWeight = INF;
        visited[current] = 1;
        for (int j = 1; j < n; ++j) {
            if(!visited[j]) {
                double len = getWeight(plane[current], plane[j]);
               //cout << len << ' ' << current << ' ' << j << endl;
                if (edges[j] > len) {
                    edges[j] = len;
                }
            }
        }
        for (int j = 1; j < n; ++j) {
            if(!visited[j] && minWeight > edges[j]) {
                minWeight = edges[j];
                next = j;
            }
        }


        //cout << "+" <<minWeight << endl;
        res += minWeight;
        current = next;
    }

    fout << fixed << setprecision(20) << res;

    fin.close();
    fout.close();
    return 0;
}

int main() {
    B();
    return 0;
}