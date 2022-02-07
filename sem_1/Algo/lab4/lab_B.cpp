
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct queue {
    int tail = -1;
    int head = 0;
    vector<int> q;

    explicit queue(int max_size) {
        q.resize(max_size);
    }
    void enqueue(int value) {
        q[++tail] = value;
    }
    int dequeue() {
        return q[head++];
    }

};


void task_B() {
    ifstream fin(R"(queue.in)");
    ofstream fout(R"(queue.out)");

    int n;
    fin >> n;
    queue q(1000000);
    for (int i = 0; i < n; i++) {
        string operation;
        fin >> operation;
        if (operation == "+") {
            int value;
            fin >> value;
            q.enqueue(value);
        } else if (operation == "-") {
            fout << q.dequeue() << endl;
        }
    }


    fin.close();
    fout.close();
}
/*
int main() {
    task_B();
    return 0;
}
 */
