//
// Created by mailo on 08.10.2021.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

struct Race {
    string country;
    string names;
};
vector<Race> runners;

vector<Race> merge(vector<Race> a, vector<Race> b) {
    vector<Race> c;
    c.resize(a.size() + b.size());
    int i = 0, j = 0;
    while (i < a.size() || j < b.size()) {
        if (j == b.size() || i < a.size() && (strcmp(a[i].country.c_str(), b[j].country.c_str()) <= 0)) {
            c[i + j] = a[i];
            i++;
        } else {
            c[i + j] = b[j];
            j++;
        }
    }
    return c;
}

vector<Race> firstHalf(vector<Race> a) {
    vector<Race> l;
    l.resize(a.size() / 2);
    for (int i = 0; i < a.size() / 2; i++) {
        l[i] = a[i];
    }
    return l;
}

vector<Race> secondHalf(vector<Race> a) {
    vector<Race> r;
    r.resize(a.size() - a.size() / 2);
    for (int i = a.size() / 2; i < a.size(); i++) {
        r[i - a.size() / 2] = a[i];
    }
    return r;
}


vector<Race> sort(vector<Race> a) {
    int n = a.size();
    if (n <= 1) {
        return a;
    }

    vector<Race> l = firstHalf(a);
    vector<Race> r = secondHalf(a);

    l = sort(l);
    r = sort(r);

    return merge(l, r);
}


int task_B() {
    ifstream fin(R"(race.in)");
    ofstream fout(R"(race.out)");
    int n = 0;
    fin >> n;

    vector<string> countries;

    string country, name;
    for (int i = 0; i < n; i++) {
        fin >> country >> name;
        Race tmp;
        tmp.country = country;
        tmp.names = name;
        runners.push_back(tmp);
    }

    runners = sort(runners);

    string tmp;
    for (Race &i: runners) {
        if (strcmp(tmp.c_str(), i.country.c_str()) != 0) {
            fout << "=== " << i.country << " ===" << endl;
        }
        fout << i.names << endl;
        tmp = i.country;
    }


    fin.close();
    fout.close();
    return 0;
}