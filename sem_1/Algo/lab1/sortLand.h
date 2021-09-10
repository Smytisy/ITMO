//
// Created by mailo on 10.09.2021.
//

#ifndef ALGOLAB1_SORTLAND_H
#define ALGOLAB1_SORTLAND_H

#endif //ALGOLAB1_SORTLAND_H


using namespace std;

int sortLand() {
    ifstream fin(R"(C:\Users\mailo\CLionProjects\algoLab1\files\turtle.in.txt)");
    ofstream fout(R"(C:\Users\mailo\CLionProjects\algoLab1\files\turtle.out.txt)");
    int n;
    fin >> n;
    long A[n][2];
    long count = 1;
    float tmp;
    for(int i = 0; i < n; i++) {
        fin >> tmp;
        A[i][0] = static_cast<long>(tmp*100);
        A[i][1] = count;
        count++;
    }

    long tmp1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - 1; j++) {
            if(A[j][0] > A[j + 1][0]) {
                tmp1 = A[j][0];
                A[j][0] = A[j+1][0];
                A[j+1][0] = tmp1;

                tmp1 = A[j][1];
                A[j][1] = A[j+1][1];
                A[j+1][1] = tmp1;
            }
        }
    }
    fout << A[0][1] << ' ' << A[n / 2][1] << ' ' << A[n - 1][1] << endl;


    fout.close();
    fin.close();
    return 0;
}
