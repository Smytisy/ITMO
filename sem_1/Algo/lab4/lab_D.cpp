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

int expression(int a, int b, char o) {
    if(o == '+')
        return a + b;
    if(o == '-')
        return a - b;
    if(o == '*')
        return a * b;
}


int result(const string &line) {
    stack s(10000);
    for (char a: line) {
        if (a == ' ') {
            continue;
        }
        if (isdigit(a)) {
            s.push(a - '0');
        } else {
            s.push(expression(s.pop(), s.pop(), a));
        }
    }
    return s.pop();
}



void task_D() {
    ifstream fin(R"(postfix.in)");
    ofstream fout(R"(postfix.out)");
    string line;
    getline(fin, line);
    fout << result(line);
    fin.close();
    fout.close();
}
/*
int main() {
    task_D();
    return 0;
}
*/