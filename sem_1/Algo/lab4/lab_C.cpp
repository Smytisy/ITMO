//
// Created by mailo on 07.11.2021.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct stack {
    vector<int> s;
    int size = 0;

    explicit stack(int max_size) {
        s.resize(max_size);
    }

    void push(int value) {
        s[++size] = value;
    }

    int pop() {
        return s[size--];
    }
};

bool check_brackets(const string& line) {
    stack s(10000);
    for (char a: line) {
        switch (a) {
            case '(':
                s.push(1);
                break;
            case '[':
                s.push(2);
                break;
            case ']':
                if (s.size == 0 || s.pop() != 2) {
                    return false;
                }
                break;
            case ')':
                if (s.size == 0 || s.pop() != 1) {
                    return false;
                }
                break;
        }
    }
    return s.size == 0;
}



void task_C() {
    ifstream fin(R"(brackets.in)");
    ofstream fout(R"(brackets.out)");
    string line;
    while (getline(fin, line)) {
        if(check_brackets(line)) {
            fout << "YES" << endl;
        } else {
            fout << "NO" << endl;
        }
    }
    fin.close();
    fout.close();
}
/*
int main() {
    task_C();
    return 0;
}
 */

