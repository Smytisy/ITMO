//
// Created by mailo on 10.09.2021.
//

#ifndef ALGOLAB1_TURTLE_H
#define ALGOLAB1_TURTLE_H

#endif //ALGOLAB1_TURTLE_H

int turtle() {
    ifstream fin(R"(C:\Users\mailo\CLionProjects\algoLab1\files\turtle.in.txt)");
    ofstream fout(R"(C:\Users\mailo\CLionProjects\algoLab1\files\turtle.out.txt)");
    int h, w;

    fin >> h >> w;
    long Food[h][w];

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            fin >> Food[i][j];
        }
    }

    long predLeft, predDown;
    for(int i1 = h - 1; i1 > -1; i1--) {
        for(int i2 = 0; i2 < w; i2++) {
            predLeft = i2 - 1 < 0 ? 0 : Food[i1][i2 - 1];
            predDown = i1 + 1 < h ? Food[i1 + 1][i2] : 0;
            Food[i1][i2] = predLeft > predDown ? Food[i1][i2] + predLeft : Food[i1][i2] + predDown;
        }
    }
    fout << Food[0][w-1] << endl;

    fout.close();
    fin.close();
    return 0;
}
