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


void task_A() {
    ifstream fin(R"(stack.in)");
    ofstream fout(R"(stack.out)");

    int n;
    fin >> n;
    stack s(1000000);
    for (int i = 0; i < n; i++) {
        string operation;
        fin >> operation;
        if (operation == "+") {
            int value;
            fin >> value;
            s.push(value);
        } else if (operation == "-") {
            fout << s.pop() << endl;
        }
    }

    fin.close();
    fout.close();
}
/*
int main() {
    task_A();
    return 0;
}
 */