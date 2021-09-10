//
// Created by mailo on 10.09.2021.
//

#ifndef ALGOLAB1_SMALLSORT_H
#define ALGOLAB1_SMALLSORT_H

#endif //ALGOLAB1_SMALLSORT_H

int smallSort() {
    ifstream fin(R"(C:\Users\mailo\CLionProjects\algoLab1\files\turtle.in.txt)");
    ofstream fout(R"(C:\Users\mailo\CLionProjects\algoLab1\files\turtle.out.txt)");
    int n;
    fin >> n;
    long long A[n];

    for(int i = 0; i < n; i++) {
        fin >> A[i];
    }

    long long tmp;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - 1; j++) {
            if(A[j] > A[j + 1]) {
                tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        fout << A[i] << ' ';
    }


    fout.close();
    fin.close();
    return 0;
}