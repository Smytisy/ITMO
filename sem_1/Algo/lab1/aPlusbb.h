//
// Created by mailo on 10.09.2021.
//

#ifndef ALGOLAB1_APLUSBB_H
#define ALGOLAB1_APLUSBB_H

#endif //ALGOLAB1_APLUSBB_H

int aPlusbb() {
    ifstream fin(R"(C:\Users\mailo\CLionProjects\algoLab1\files\turtle.in.txt)");
    ofstream fout(R"(C:\Users\mailo\CLionProjects\algoLab1\files\turtle.out.txt)");
    long long a, b;
    fin >> a >> b;
    fout <<  a + b*b;

    fout.close();
    fin.close();
    return 0;
}