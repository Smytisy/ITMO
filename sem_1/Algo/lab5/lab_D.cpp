//
// Created by mailo on 17.11.2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "queue"
#include <map>

using namespace std;

class Queue {
    queue<uint16_t> queue;

public:
    uint16_t get() {
        uint16_t res = queue.front();
        queue.pop();
        return res;
    }

    void put(int x) {
        queue.push((uint16_t) x % 65536);
    }
};

void get_label(vector<string> &lines, map<string, int> &label) {
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i][0] == ':') {
            label[lines[i].substr(1)] = i;
        }
    }
}


void quack(vector<string> &lines, ofstream &fout) {
    map<string, int> label;
    get_label(lines, label);
    Queue queue;
    vector<uint16_t> registers;
    registers.resize(26);

    for (int i = 0; i < lines.size(); i++) {
        uint16_t x, y;
        char command = lines[i][0];
        switch (command) {
            case ':':
                break;
            case '+':
                x = queue.get();
                y = queue.get();
                queue.put(x + y);
                break;
            case '-':
                x = queue.get();
                y = queue.get();
                queue.put(x - y);
                break;
            case '*':
                x = queue.get();
                y = queue.get();
                queue.put(x * y);
                break;
            case '/':
                x = queue.get();
                y = queue.get();
                queue.put(y != 0 ? x / y : 0);
                break;
            case '%':
                x = queue.get();
                y = queue.get();
                queue.put(y != 0 ? x % y : 0);
                break;
            case '>':
                registers[abs('a' - lines[i][1])] = queue.get();
                break;
            case '<':
                queue.put(registers[abs('a' - lines[i][1])]);
                break;
            case 'P':
                if (lines[i].length() == 1) {
                    fout << queue.get() << endl;
                } else {
                    fout << registers[abs('a' - lines[i][1])] << endl;
                }
                break;
            case 'C':
                if (lines[i].length() == 1) {
                    fout << (char) (queue.get() % 256);
                } else {
                    fout << (char) (registers[abs('a' - lines[i][1])] % 256);
                }
                break;
            case 'J':
                i = label[lines[i].substr(1)];
                break;
            case 'Z':
                if (registers[abs('a' - lines[i][1])] == 0) {
                    i = label[lines[i].substr(2)];
                }
                break;
            case 'E':
                if (registers[abs('a' - lines[i][1])] == registers[abs('a' - lines[i][2])]) {
                    i = label[lines[i].substr(3)];
                }
                break;
            case 'G':
                if (registers[abs('a' - lines[i][1])] > registers[abs('a' - lines[i][2])]) {
                    i = label[lines[i].substr(3)];
                }
                break;
            case 'Q':
                i = 1 + lines.size();
                break;
            default:
                queue.put(stoi(lines[i]));
        }
    }
}


void task_D() {
    ifstream fin(R"(quack.in)");
    ofstream fout(R"(quack.out)");
    string line;
    vector<string> lines;
    while (getline(fin, line)) {
        lines.push_back(line);
    }
    quack(lines, fout);
    fin.close();
    fout.close();
}
/*
int main() {
    task_D();
    return 0;
}
*/
