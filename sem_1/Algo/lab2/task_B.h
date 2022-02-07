#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

struct Race {
    string country;
    vector<string> names;
};
vector<Race> runners;

vector<string> merge(vector<string> a, vector<string> b) {
    vector<string> c;
    c.resize(a.size() + b.size());
    int i = 0, j = 0;
    while (i < a.size() || j < b.size()) {
        if (j == b.size() || i < a.size() && (strcmp(a[i].c_str(), b[j].c_str()) < 0)) {
            c[i + j] = a[i];
            i++;
        } else {
            c[i + j] = b[j];
            j++;
        }
    }
    return c;
}

vector<string> firstHalf(vector<string> a) {
    vector<string> l;
    l.resize(a.size() / 2);
    for (int i = 0; i < a.size() / 2; i++) {
        l[i] = a[i];
    }
    return l;
}

vector<string> secondHalf(vector<string> a) {
    vector<string> r;
    r.resize(a.size() - a.size() / 2);
    for (int i = a.size() / 2; i < a.size(); i++) {
        r[i - a.size() / 2] = a[i];
    }
    return r;
}


vector<string> sort(vector<string> a) {
    int n = a.size();
    if (n <= 1) {
        return a;
    }

    vector<string> l = firstHalf(a);
    vector<string> r = secondHalf(a);

    l = sort(l);
    r = sort(r);

    return merge(l, r);
}



int task_B() {
    ifstream fin(R"(race.in)");
    ofstream fout(R"(race.out)");
    int n = 0;
    fin >> n;

    bool country_contain;
    vector<string> countries;

    string country, name;
    for (int i = 0; i < n; i++) {
        fin >> country >> name;


        country_contain = false;
        for (int j = 0; j < runners.size(); j++) {
            if (strcmp(runners[j].country.c_str(), country.c_str()) == 0) {
                runners[j].names.push_back(name);
                country_contain = true;
                break;
            }
        }
        if (!country_contain) {
            Race tmp;
            tmp.country = country;
            tmp.names.push_back(name);
            countries.push_back(country);
            runners.push_back(tmp);

        }
    }

    countries = sort(countries);


    for (int i = 0; i < countries.size(); i++) {
        for (int j = 0; j < runners.size(); j++) {
            if (strcmp(runners[j].country.c_str(), countries[i].c_str()) == 0) {
                fout << "=== " << countries[i] << " ===" << endl;
                for (string &item: runners[j].names) {
                    fout << item << endl;
                }
                break;
            }
        }
    }
    return 0;
}

