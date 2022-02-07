//
// Created by mailo on 17.10.2021.
//
/*

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
struct Node {
    int value;
    int line;
};
vector<Node> array_heap;
int heap_size;


void Min_Heapify(int i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int smallest;
    if (l <= heap_size && array_heap[l].value < array_heap[i].value) {
        smallest = l;
    } else smallest = i;
    if (r <= heap_size && array_heap[r].value < array_heap[smallest].value) {
        smallest = r;
    }
    if (smallest != i) {
        swap(array_heap[i], array_heap[smallest]);
        Min_Heapify(smallest);
    }
}


int Heap_Extract_Min() {
    if (heap_size < 1) {
        return UINT32_MAX - 1;
    }

    int min = array_heap[1].value;
    array_heap[1] = array_heap[heap_size];
    heap_size -= 1;
    Min_Heapify(1);
    return min;
}

int find_line(int key) {
    for (int i = 1; i <= heap_size; i++) {
        if (array_heap[i].line == key) {
            return i;
        }
    }
}

void Heap_Decrease_Key(int line, int key) {
    int i = find_line(line);
    array_heap[i].value = key;
    while (i > 1 && array_heap[i / 2].value > array_heap[i].value) {
        swap(array_heap[i], array_heap[i / 2]);
        i = i / 2;
    }
}


void Min_Heap_Push(int key, int l) {
    heap_size += 1;
    array_heap[heap_size].value = key;
    array_heap[heap_size].line = l;
    int i = heap_size;
    while (i > 1 && array_heap[i / 2].value > array_heap[i].value) {
        swap(array_heap[i], array_heap[i / 2]);
        i = i / 2;
    }
}


void task_D() {
    ifstream fin(R"(priorityqueue.in)");
    ofstream fout(R"(priorityqueue.out)");
    array_heap.resize(1000001);
    heap_size = 0;
    int line = 0;


    while (!fin.eof()) {
        string oper;
        fin >> oper;
        line++;

        if (oper == "push") {
            int key;
            fin >> key;
            Min_Heap_Push(key, line);

        } else if (oper == "extract-min") {
            int tmp = Heap_Extract_Min();
            if (tmp == UINT32_MAX - 1) {
                fout << "*" << endl;
            } else {
                fout << tmp << endl;
            }

        } else if (oper == "decrease-key") {
            int number, value;
            fin >> number >> value;
            Heap_Decrease_Key(number, value);
        }
    }

    fin.close();
    fout.close();
}
*/

