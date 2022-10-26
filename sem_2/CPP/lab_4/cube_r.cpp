#include "cube_r.h"




cube_r::cube_r() {
    for (int j = 0; j < 9; j++)
        this->cube[0][j] = 'G';
    for (int j = 0; j < 9; j++)
        this->cube[1][j] = 'B';
    for (int j = 0; j < 9; j++)
        this->cube[2][j] = 'O';
    for (int j = 0; j < 9; j++)
        this->cube[3][j] = 'R';
    for (int j = 0; j < 9; j++)
        this->cube[4][j] = 'W';
    for (int j = 0; j < 9; j++)
        this->cube[5][j] = 'Y';
}

cube_r::cube_r(const cube_r &toCpy) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            this->cube[i][j] = toCpy.cube[i][j];
        }
    }
}


void cube_r::turn_clockwise(const cube_r& tmpCube, int side) {
    this->cube[side][8] = tmpCube.cube[side][2];
    this->cube[side][7] = tmpCube.cube[side][5];
    this->cube[side][6] = tmpCube.cube[side][8];
    this->cube[side][3] = tmpCube.cube[side][7];
    this->cube[side][0] = tmpCube.cube[side][6];
    this->cube[side][1] = tmpCube.cube[side][3];
    this->cube[side][2] = tmpCube.cube[side][0];
    this->cube[side][5] = tmpCube.cube[side][1];
}


void cube_r::U() {
    // write
    cube_r tmpCube(*this);
    turn_clockwise(tmpCube, 4);
    for (int i = 0; i < 3; i++) {
        this->cube[0][i] = tmpCube.cube[3][i];
        this->cube[2][i] = tmpCube.cube[0][i];
        this->cube[1][i] = tmpCube.cube[2][i];
        this->cube[3][i] = tmpCube.cube[1][i];
    }
}

void cube_r::Ui() {
    U();
    U();
    U();
}

void cube_r::D() {
    //write
    cube_r tmpCube(*this);
    turn_clockwise(tmpCube, 5);
    for (int i = 6; i < 9; i++) {
        this->cube[0][i] = tmpCube.cube[2][i];
        this->cube[2][i] = tmpCube.cube[1][i];
        this->cube[1][i] = tmpCube.cube[3][i];
        this->cube[3][i] = tmpCube.cube[0][i];
    }
}

void cube_r::Di() {
    D();
    D();
    D();
}

void cube_r::F() {
    //write
    cube_r tmpCube(*this);
    turn_clockwise(tmpCube, 0);

    this->cube[4][6] = tmpCube.cube[2][8];
    this->cube[4][7] = tmpCube.cube[2][5];
    this->cube[4][8] = tmpCube.cube[2][2];

    this->cube[5][0] = tmpCube.cube[3][6];
    this->cube[5][1] = tmpCube.cube[3][3];
    this->cube[5][2] = tmpCube.cube[3][0];

    this->cube[2][2] = tmpCube.cube[5][0];
    this->cube[2][5] = tmpCube.cube[5][1];
    this->cube[2][8] = tmpCube.cube[5][2];

    this->cube[3][0] = tmpCube.cube[4][6];
    this->cube[3][3] = tmpCube.cube[4][7];
    this->cube[3][6] = tmpCube.cube[4][8];
}

void cube_r::Fi() {
    F();
    F();
    F();
}

void cube_r::B() {
    //write
    cube_r tmpCube(*this);
    turn_clockwise(tmpCube, 1);

    this->cube[4][0] = tmpCube.cube[3][2];
    this->cube[4][1] = tmpCube.cube[3][5];
    this->cube[4][2] = tmpCube.cube[3][8];

    this->cube[5][8] = tmpCube.cube[2][6];
    this->cube[5][7] = tmpCube.cube[2][3];
    this->cube[5][6] = tmpCube.cube[2][0];

    this->cube[2][6] = tmpCube.cube[4][0];
    this->cube[2][3] = tmpCube.cube[4][1];
    this->cube[2][0] = tmpCube.cube[4][2];

    this->cube[3][2] = tmpCube.cube[5][8];
    this->cube[3][5] = tmpCube.cube[5][7];
    this->cube[3][8] = tmpCube.cube[5][6];
}

void cube_r::Bi() {
    B();
    B();
    B();
}

void cube_r::L() {
    //write
    cube_r tmpCube(*this);
    turn_clockwise(tmpCube, 2);

    this->cube[0][0] = tmpCube.cube[4][0];
    this->cube[0][3] = tmpCube.cube[4][3];
    this->cube[0][6] = tmpCube.cube[4][6];

    this->cube[5][0] = tmpCube.cube[0][0];
    this->cube[5][3] = tmpCube.cube[0][3];
    this->cube[5][6] = tmpCube.cube[0][6];

    this->cube[4][0] = tmpCube.cube[1][8];
    this->cube[4][3] = tmpCube.cube[1][5];
    this->cube[4][6] = tmpCube.cube[1][2];

    this->cube[1][8] = tmpCube.cube[5][0];
    this->cube[1][5] = tmpCube.cube[5][3];
    this->cube[1][2] = tmpCube.cube[5][6];
}

void cube_r::Li() {
    L();
    L();
    L();
}

void cube_r::R() {
    //write
    cube_r tmpCube(*this);
    turn_clockwise(tmpCube, 3);

    this->cube[0][2] = tmpCube.cube[5][2];
    this->cube[0][5] = tmpCube.cube[5][5];
    this->cube[0][8] = tmpCube.cube[5][8];

    this->cube[5][2] = tmpCube.cube[1][6];
    this->cube[5][5] = tmpCube.cube[1][3];
    this->cube[5][8] = tmpCube.cube[1][0];

    this->cube[4][2] = tmpCube.cube[0][2];
    this->cube[4][5] = tmpCube.cube[0][5];
    this->cube[4][8] = tmpCube.cube[0][8];

    this->cube[1][6] = tmpCube.cube[4][2];
    this->cube[1][3] = tmpCube.cube[4][5];
    this->cube[1][0] = tmpCube.cube[4][8];
}

void cube_r::Ri() {
    R();
    R();
    R();
}

void cube_r::print() {
    for(int i = 0; i < 6; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << this->cube[i][j];
            if (j % 3 == 2) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

void cube_r::read_file() {
    std::ifstream fin(R"(C:\Users\mailo\CLionProjects\Rubik_Cube\input.txt)");
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 9; ++j) {
            fin >> this->cube[i][j];
        }
    }
}


