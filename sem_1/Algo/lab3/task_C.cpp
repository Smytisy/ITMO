//
// Created by mailo on 23.10.2021.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> count_sort(int index, vector<string> arr) {
    vector<string> tmp;
    tmp.resize(arr.size());

    vector<int> alphabet;
    alphabet.resize(26);
    for(auto & element : arr) {
        alphabet[element[index] - 'a']++;
    }
    for(int i = 1; i < alphabet.size(); i++) {
        alphabet[i] += alphabet[i - 1];
    }
    for(int i = (int) arr.size() - 1; i >= 0; i--) {
        tmp[alphabet[arr[i][index] - 'a'] - 1] = arr[i];
        alphabet[arr[i][index] - 'a']--;
    }
    return tmp;
}



void task_C() {
    ifstream fin(R"(radixsort.in)");
    ofstream fout(R"(radixsort.out)");
    int n, m, k;
    fin >> n >> m >> k;
    vector<string> arr;
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> arr[i];
    }
    for (int i = 0; i < k; ++i) {
        arr = count_sort(m - 1, arr);
        m--;
    }
    for (auto & element: arr){
        fout << element << endl;
    }


    fin.close();
    fout.close();
}

int main() {
    task_C();
    return 0;
}

