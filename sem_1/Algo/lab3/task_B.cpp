//
// Created by mailo on 22.10.2021.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> array_heap;
int heap_size;


void Max_Heapify(int i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int largest;
    if (l <= heap_size && array_heap[l] > array_heap[i]) {
        largest = l;
    } else largest = i;
    if (r <= heap_size && array_heap[r] > array_heap[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(array_heap[i], array_heap[largest]);
        Max_Heapify(largest);
    }
}

void Build_Max_Heap() {
    heap_size = array_heap.size() - 1;
    for (int i = (int) (array_heap.size() - 1) / 2; i >= 1; i--) {
        Max_Heapify(i);
    }
}

void HeapSort() {
    Build_Max_Heap();
    for (int i = (int) array_heap.size() - 1; i >= 2; i--) {
        swap(array_heap[1], array_heap[i]);
        heap_size -= 1;
        Max_Heapify(1);
    }
}

void task_B() {
    ifstream fin(R"(sort.in)");
    ofstream fout(R"(sort.out)");
    int n;
    fin >> n;
    array_heap.resize(n + 1);
    for (int i = 1; i < n + 1; i++) {
        fin >> array_heap[i];
    }
    HeapSort();

    for (int i = 1; i < n + 1; i++) {
        fout << array_heap[i] << ' ';
    }


    fin.close();
    fout.close();
}

