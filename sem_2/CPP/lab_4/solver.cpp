#include "solver.h"

centre solver::getCentre(cube_r &cubeR) {
    centre ans{};

    ans.centre[0] = cubeR.cube[0][4];
    ans.centre[1] = cubeR.cube[1][4];
    ans.centre[2] = cubeR.cube[2][4];
    ans.centre[3] = cubeR.cube[3][4];
    ans.centre[4] = cubeR.cube[4][4];
    ans.centre[5] = cubeR.cube[5][4];
    return ans;
}

corner solver::getCorner(cube_r &cubeR) {
    corner ans{};
    //front right top
    ans.cor[0][0] = cubeR.cube[0][2];
    ans.cor[0][1] = cubeR.cube[3][0];
    ans.cor[0][2] = cubeR.cube[4][8];
    //right back top
    ans.cor[1][0] = cubeR.cube[3][2];
    ans.cor[1][1] = cubeR.cube[1][0];
    ans.cor[1][2] = cubeR.cube[4][2];
    //back left top
    ans.cor[2][0] = cubeR.cube[1][2];
    ans.cor[2][1] = cubeR.cube[2][0];
    ans.cor[2][2] = cubeR.cube[4][0];
    //left front top
    ans.cor[3][0] = cubeR.cube[2][2];
    ans.cor[3][1] = cubeR.cube[0][0];
    ans.cor[3][2] = cubeR.cube[4][6];
    //front right down
    ans.cor[4][0] = cubeR.cube[0][8];
    ans.cor[4][1] = cubeR.cube[3][6];
    ans.cor[4][2] = cubeR.cube[5][2];
    //right back down
    ans.cor[5][0] = cubeR.cube[3][8];
    ans.cor[5][1] = cubeR.cube[1][6];
    ans.cor[5][2] = cubeR.cube[5][8];
    //back left down
    ans.cor[6][0] = cubeR.cube[1][8];
    ans.cor[6][1] = cubeR.cube[2][6];
    ans.cor[6][2] = cubeR.cube[5][6];
    //left front down
    ans.cor[7][0] = cubeR.cube[2][8];
    ans.cor[7][1] = cubeR.cube[0][6];
    ans.cor[7][2] = cubeR.cube[5][0];
    return ans;
}


edge solver::getEdge(cube_r &cubeR) {
    edge ans;
    //front top
    ans.ed[0][0] = cubeR.cube[0][1];
    ans.ed[0][1] = cubeR.cube[4][7];
    //right top
    ans.ed[1][0] = cubeR.cube[3][1];
    ans.ed[1][1] = cubeR.cube[4][5];
    //back top
    ans.ed[2][0] = cubeR.cube[1][1];
    ans.ed[2][1] = cubeR.cube[4][1];
    //right top
    ans.ed[3][0] = cubeR.cube[2][1];
    ans.ed[3][1] = cubeR.cube[4][3];
    //front right
    ans.ed[4][0] = cubeR.cube[0][5];
    ans.ed[4][1] = cubeR.cube[3][3];
    //right back
    ans.ed[5][0] = cubeR.cube[3][5];
    ans.ed[5][1] = cubeR.cube[1][3];
    //back left
    ans.ed[6][0] = cubeR.cube[1][5];
    ans.ed[6][1] = cubeR.cube[2][3];
    //left front
    ans.ed[7][0] = cubeR.cube[2][5];
    ans.ed[7][1] = cubeR.cube[0][3];
    //front down
    ans.ed[8][0] = cubeR.cube[0][7];
    ans.ed[8][1] = cubeR.cube[5][1];
    //right down
    ans.ed[9][0] = cubeR.cube[3][7];
    ans.ed[9][1] = cubeR.cube[5][5];
    // back down
    ans.ed[10][0] = cubeR.cube[1][7];
    ans.ed[10][1] = cubeR.cube[5][7];
    // left down
    ans.ed[11][0] = cubeR.cube[2][7];
    ans.ed[11][1] = cubeR.cube[5][3];
    return ans;
}


solver::solver(cube_r& cubeR) {
    step0(cubeR);
    step1(cubeR);
    step2(cubeR);
    step3(cubeR);
    step4(cubeR);
    step5(cubeR);
    step6(cubeR);
    step7(cubeR);
}

void solver::move(int number, cube_r &cubeR) {

    switch (number) {
        case 4:
            cubeR.U();
            scramble[position] = "U";
            break;
        case 5:
            cubeR.D();
            scramble[position] = "D";
            break;
        case 0:
            cubeR.F();
            scramble[position] = "F";
            break;
        case 2:
            cubeR.B();
            scramble[position] = "B";
            break;
        case 3:
            cubeR.L();
            scramble[position] = "L";
            break;
        case 1:
            cubeR.R();
            scramble[position] = "R";
            break;
        case 10:
            cubeR.Ui();
            scramble[position] = "U'";
            break;
        case 11:
            cubeR.Di();
            scramble[position] = "D'";
            break;
        case 6:
            cubeR.Fi();
            scramble[position] = "F'";
            break;
        case 8:
            cubeR.Bi();
            scramble[position] = "B'";
            break;
        case 9:
            cubeR.Li();
            scramble[position] = "L'";
            break;
        case 7:
            cubeR.Ri();
            scramble[position] = "R'";
            break;
        default:
            break;
    }
    position++;
}





void solver::step0(cube_r& cubeR) {
    bool solve = 0;
    edge temp = getEdge(cubeR);
    if ((temp.ed[0][1] == 'W') && (temp.ed[1][1] == 'W')
        && (temp.ed[2][1] == 'W') && (temp.ed[3][1] == 'W'))
        solve = 1;

    while (solve == 0) {
        // add from top layer
        for (int i = 0; i < 4; i++) {
            if (temp.ed[i][0] == 'W') {
                move(i, cubeR);
                temp = getEdge(cubeR);
                while (temp.ed[(i + 1) % 4][1] == 'W') {
                    move(4, cubeR);
                    temp = getEdge(cubeR);
                }
                move((i + 1) % 4, cubeR);
                temp = getEdge(cubeR);
            }
        }
        // add from middle layer
        for (int i = 4; i < 8; i++) {
            if (temp.ed[i][0] == 'W') {
                while (temp.ed[(i + 1) % 4][1] == 'W') {
                    move(4, cubeR);
                    temp = getEdge(cubeR);
                }
                move((i + 1) % 4, cubeR);
                temp = getEdge(cubeR);
            }
            if (temp.ed[i][1] == 'W') {
                while (temp.ed[(i - 1) % 4][1] == 'W') {
                    move(4, cubeR);
                    temp = getEdge(cubeR);
                }
                move((i % 4) + 6, cubeR);
                temp = getEdge(cubeR);
            }
        }
        // add from bottom layer
        for (int i = 8; i < 12; i++) {
            if (temp.ed[i][0] == 'W') {
                while (temp.ed[i % 4][1] == 'W') {
                    move(4, cubeR);
                    temp = getEdge(cubeR);
                }
                move((i % 4) + 6, cubeR);
                temp = getEdge(cubeR);
                while (temp.ed[(i + 1) % 4][1] == 'W') {
                    move(4, cubeR);
                    temp = getEdge(cubeR);
                }
                move((i + 1) % 4, cubeR);
                temp = getEdge(cubeR);
            }

            if (temp.ed[i][1] == 'W') {
                while (temp.ed[i % 4][1] == 'W') {
                    move(4, cubeR);
                    temp = getEdge(cubeR);
                }
                move((i % 4), cubeR);
                temp = getEdge(cubeR);
                move((i % 4), cubeR);
                temp = getEdge(cubeR);
            }
        }
        if ((temp.ed[0][1] == 'W') && (temp.ed[1][1] == 'W')
            && (temp.ed[2][1] == 'W') && (temp.ed[3][1] == 'W'))
            solve = 1;
    }
    return;
}

void solver::step1(cube_r &cubeR) {
    bool solve = 0;

    edge temp = getEdge(cubeR);

    char side[4] = {'G', 'R', 'B', 'O'};
    if ((temp.ed[0][0] == 'G') && (temp.ed[1][0] == 'R')
        && (temp.ed[2][0] == 'B') && (temp.ed[3][0] == 'O'))
        solve = 1;

    if (solve == 0) {
        int i;
        for (i = 0; i < 4; i++) {
            while ((temp.ed[i][1] != 'W') || (temp.ed[i][0] != side[i])) {
                move(4, cubeR);
                temp = getEdge(cubeR);
            }
            move(i, cubeR);
            move(i, cubeR);
            temp = getEdge(cubeR);
        }
        move(0, cubeR);
        move(0, cubeR);
        move(1, cubeR);
        move(1, cubeR);
        move(2, cubeR);
        move(2, cubeR);
        move(3, cubeR);
        move(3, cubeR);
    }
    return;
}

void solver::step2(cube_r &cubeR) {
    bool solve = 1;

    corner temp1 = getCorner(cubeR);

    char side[4] = {'G', 'R', 'B', 'O'};

    int ops = 0;
    for (int i = 0; i < 4; i++) {
        if ((temp1.cor[i][0] != side[i]) || (temp1.cor[i][1] != side[(i + 1) % 4])
            || (temp1.cor[i][2] != 'W')) {
            solve = 0;
            break;
        }

    }
    while (solve == 0) {
        // add to top
        for (int i = 0; i < 4; i++) {
            if (temp1.cor[i + 4][0] == 'W') {
                int j;
                for (j = 0; j < 4; j++) {
                    if (side[j] == temp1.cor[i + 4][1]) {
                        ops = (j - i + 3) % 4;
                        break;
                    }
                }
                for (int k = 0; k < ops; k++)
                    move(5, cubeR);
                move((j + 3) % 4, cubeR);
                move(5, cubeR);
                move((j + 3) % 4 + 6, cubeR);
                temp1 = getCorner(cubeR);
            } else if (temp1.cor[i + 4][1] == 'W') {
                ops = 0;

                int j;
                for (j = 0; j < 4; j++) {
                    if (side[j] == temp1.cor[i + 4][0]) {
                        ops = (j - i + 4) % 4;
                        break;
                    }
                }
                for (int k = 0; k < ops; k++)
                    move(5, cubeR);
                move((j + 1) % 4 + 6, cubeR);
                move(11, cubeR);
                move((j + 1) % 4, cubeR);
                temp1 = getCorner(cubeR);
            } else if (temp1.cor[i + 4][2] == 'W') {
                ops = 0;

                int j;
                for (j = 0; j < 4; j++) {
                    if (side[j] == temp1.cor[i + 4][0]) {
                        ops = (j - i + 3) % 4;
                        break;
                    }
                }
                for (int k = 0; k < ops; k++)
                    move(5, cubeR);
                move((j + 3) % 4, cubeR);
                move(5, cubeR);
                move(5, cubeR);
                move((j + 3) % 4 + 6, cubeR);
                move(11, cubeR);
                move((j + 3) % 4, cubeR);
                move(5, cubeR);
                move((j + 3) % 4 + 6, cubeR);
                temp1 = getCorner(cubeR);
            }
        }
        // fix wrong corners from top
        for (int i = 0; i < 4; i++) {
            if (temp1.cor[i][0] == 'W') {
                while ((temp1.cor[i + 4][0] == 'W')
                       || (temp1.cor[i + 4][1] == 'W') || (temp1.cor[i + 4][2] == 'W'))
                    move(5, cubeR);
                move(i, cubeR);
                move(5, cubeR);
                move(i + 6, cubeR);
                temp1 = getCorner(cubeR);
                ops = 0;
                int j;
                for (j = 0; j < 4; j++) {
                    if (side[j] == temp1.cor[(i + 1) % 4 + 4][1]) {
                        ops = (j - i + 2) % 4;
                        break;
                    }
                }
                for (int k = 0; k < ops; k++)
                    move(5, cubeR);
                move((j + 3) % 4, cubeR);
                move(5, cubeR);
                move((j + 3) % 4 + 6, cubeR);
                temp1 = getCorner(cubeR);
            }

            if (temp1.cor[i][1] == 'W') {
                while ((temp1.cor[i + 4][0] == 'W')
                       || (temp1.cor[i + 4][1] == 'W') || (temp1.cor[i + 4][2] == 'W'))
                    move(5, cubeR);
                move((i + 1) % 4 + 6, cubeR);
                move(11, cubeR);
                move((i + 1) % 4, cubeR);
                temp1 = getCorner(cubeR);
                ops = 0;
                int j;
                for (j = 0; j < 4; j++) {
                    if (side[j] == temp1.cor[(i + 3) % 4 + 4][0]) {
                        ops = (j - i + 3) % 4;
                        break;
                    }
                }
                for (int k = 0; k < ops; k++)
                    move(5, cubeR);
                move((j + 1) % 4 + 6, cubeR);
                move(11, cubeR);
                move((j + 1) % 4, cubeR);
                temp1 = getCorner(cubeR);
            }

            if ((temp1.cor[i][2] == 'W') && (temp1.cor[i][0] != side[i])) {
                move(i, cubeR);
                move(5, cubeR);
                move(i + 6, cubeR);
                temp1 = getCorner(cubeR);
                ops = 0;
                int j;
                for (j = 0; j < 4; j++) {
                    if (side[j] == temp1.cor[(i + 1) % 4 + 4][0]) {
                        ops = (j - i + 3) % 4;
                        break;
                    }
                }
                for (int k = 0; k < ops; k++)
                    move(5, cubeR);
                move((j + 1) % 4 + 6, cubeR);
                move(11, cubeR);
                move((j + 1) % 4, cubeR);
                temp1 = getCorner(cubeR);
            }
        }

        solve = 1;
        for (int i = 0; i < 4; i++) {
            if ((temp1.cor[i][2] != 'W') || (temp1.cor[i][0] != side[i])) {
                solve = 0;
                break;
            }
        }
    }
}

void solver::step3(cube_r &cubeR) {
    bool solve = 1;

    edge temp1 = getEdge(cubeR);

    char side[4] = {'G', 'R', 'B', 'O'};
    for (int i = 0; i < 4; i++) {
        if ((temp1.ed[i + 4][0] != side[i]) || (temp1.ed[i + 4][1] != side[(i + 1) % 4])) {
            solve = 0;
            break;
        }
    }
    while (solve == 0) {
        for (int i = 0; i < 4; i++) {
            if ((temp1.ed[i + 8][0] != 'Y') && (temp1.ed[i + 8][1] != 'Y')) {
                // set edge above sides
                int ops = 0;
                int j = 0;
                for (j = 0; j < 4; j++) {
                    if (temp1.ed[i + 8][0] == side[j]) {
                        ops = (j - i + 4) % 4;
                        break;
                    }
                }
                for (int m = 0; m < ops; m++)
                    move(5, cubeR);
                // go left
                if (temp1.ed[i + 8][1] == side[(j + 3) % 4]) {
                    move(5, cubeR);
                    move((j + 3) % 4, cubeR);
                    move(11, cubeR);
                    move((j + 3) % 4 + 6, cubeR);
                    move(11, cubeR);
                    move(j + 6, cubeR);
                    move(5, cubeR);
                    move(j, cubeR);
                    temp1 = getEdge(cubeR);
                }
                    // go right
                else {
                    move(11, cubeR);
                    move((j + 1) % 4 + 6, cubeR);
                    move(5, cubeR);
                    move((j + 1) % 4, cubeR);
                    move(5, cubeR);
                    move(j, cubeR);
                    move(11, cubeR);
                    move(j + 6, cubeR);
                    temp1 = getEdge(cubeR);
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            if (temp1.ed[i + 4][0] == side[i] && temp1.ed[i + 4][1] == side[(i + 1) % 4])
                continue;
            else if ((temp1.ed[i + 4][0] != 'Y') && (temp1.ed[i + 4][1] != 'Y')) {
                // while(temp1.ed[i+8][0]!='Y'&&temp1.ed[i+8][1]!='Y')
                // 	move(5,rubic);
                move((i + 1) % 4 + 6, cubeR);
                move(5, cubeR);
                move((i + 1) % 4, cubeR);
                move(5, cubeR);
                move(i, cubeR);
                move(11, cubeR);
                move(i + 6, cubeR);
                temp1 = getEdge(cubeR);
            }
        }
        solve = 1;
        for (int i = 0; i < 4; i++) {
            if ((temp1.ed[i + 4][0] != side[i]) || (temp1.ed[i + 4][1] != side[(i + 1) % 4])) {
                solve = 0;
                break;
            }
        }
    }
}

void solver::step4(cube_r &cubeR) {
    int solve = 1;

    edge temp1 = getEdge(cubeR);
    for (int i = 0; i < 4; i++) {
        if (temp1.ed[i + 8][1] != 'Y') {
            solve = 0;
            break;
        }
    }
    while (solve == 0) {
        for (int i = 0; i < 4; i++) {
            if (temp1.ed[i + 8][1] != 'Y') {
                move(i + 6, cubeR);
                move((i + 1) % 4 + 6, cubeR);
                move(11, cubeR);
                move((i + 1) % 4, cubeR);
                move(5, cubeR);
                move(i, cubeR);
                temp1 = getEdge(cubeR);
                break;
            }
        }
        solve = 1;
        for (int i = 0; i < 4; i++) {
            if (temp1.ed[i + 8][1] != 'Y') {
                solve = 0;
                break;
            }
        }
    }
    return;
}

void solver::step5(cube_r &cubeR) {
    int count = 0;

    corner temp1 = getCorner(cubeR);

    for (int i = 0; i < 4; i++) {
        if (temp1.cor[i + 4][2] != 'Y') {
            count++;
        }
    }

    while (count > 0) {
        while (temp1.cor[4][2] == 'Y') {
            move(11, cubeR);
            temp1 = getCorner(cubeR);
        }
        while (temp1.cor[4][2] != 'Y') {
            move(1, cubeR);
            move(4, cubeR);
            move(7, cubeR);
            move(10, cubeR);
            move(1, cubeR);
            move(4, cubeR);
            move(7, cubeR);
            move(10, cubeR);
            temp1 = getCorner(cubeR);
        }
        count--;
    }
    return;
}

void solver::step6(cube_r &cubeR) {
    bool solve = 1;

    corner temp1 = getCorner(cubeR);

    char side[4] = {'G', 'R', 'B', 'O'};

    for (int i = 0; i < 4; i++) {
        if (temp1.cor[i + 4][1] != temp1.cor[(i + 1) % 4 + 4][0]) {
            solve = 0;
            break;
        }
    }
    // if 4 sides are G G, R R, B B, O O, but on the wrong face
    if (solve == 1 && temp1.cor[4][0] != 'G') {
        int i;
        for (i = 0; i < 4; i++)
            if (temp1.cor[4][0] == side[i])
                break;
        for (int p = 0; p < i; p++)
            move(5, cubeR);
        return;
    }

    while (solve == 0) {
        int j = 0;
        for (int i = 0; i < 4; i++) {
            if (temp1.cor[i + 4][1] == temp1.cor[(i + 1) % 4 + 4][0]) {
                int ops;
                for (j = 0; j < 4; j++) {
                    if (side[j] == temp1.cor[i + 4][1]) {
                        ops = (j - i + 7) % 4;
                        break;
                    }
                }
                for (int p = 0; p < ops; p++)
                    move(5, cubeR);
                break;
            }
        }
        move((j + 1) % 4 + 6, cubeR);
        move((j + 2) % 4, cubeR);
        move((j + 1) % 4 + 6, cubeR);
        move(j, cubeR);
        move(j, cubeR);
        move((j + 1) % 4, cubeR);
        move((j + 2) % 4 + 6, cubeR);
        move((j + 1) % 4 + 6, cubeR);
        move(j, cubeR);
        move(j, cubeR);
        move((j + 1) % 4, cubeR);
        move((j + 1) % 4, cubeR);
        move(11, cubeR);
        temp1 = getCorner(cubeR);

        solve = 1;
        for (int i = 0; i < 4; i++) {
            if ((temp1.cor[i + 4][1] != temp1.cor[(i + 1) % 4 + 4][0])) {
                solve = 0;
                break;
            }
        }
    }
    return;
}

void solver::step7(cube_r &cubeR) {
    int count = 0;

    edge temp1 = getEdge(cubeR);

    char side[4] = {'G', 'R', 'B', 'O'};

    for (int i = 0; i < 4; i++) {
        if (temp1.ed[i + 8][0] == side[i])
            count++;
    }
    while (count != 4) {
        int number = 0;
        int j = 0;
        if (count == 1) {
            // decide which direction to go
            for (j = 0; j < 4; j++)
                if (temp1.ed[j + 8][0] == side[j])
                    break;
            if (temp1.ed[(j + 1) % 4 + 8][0] != side[(j + 2) % 4])
                number = 1;
        }
        switch (number) {
            // clockwise
            case 0: {
                move((j + 2) % 4, cubeR);
                move((j + 2) % 4, cubeR);
                move(5, cubeR);
                move((j + 3) % 4, cubeR);
                move((j + 1) % 4 + 6, cubeR);
                move((j + 2) % 4, cubeR);
                move((j + 2) % 4, cubeR);
                move((j + 3) % 4 + 6, cubeR);
                move((j + 1) % 4, cubeR);
                move(5, cubeR);
                move((j + 2) % 4, cubeR);
                move((j + 2) % 4, cubeR);
                temp1 = getEdge(cubeR);
                break;
            }
                // anticlockwise
            case 1: {
                move((j + 2) % 4, cubeR);
                move((j + 2) % 4, cubeR);
                move(11, cubeR);
                move((j + 3) % 4, cubeR);
                move((j + 1) % 4 + 6, cubeR);
                move((j + 2) % 4, cubeR);
                move((j + 2) % 4, cubeR);
                move((j + 3) % 4 + 6, cubeR);
                move((j + 1) % 4, cubeR);
                move(11, cubeR);
                move((j + 2) % 4, cubeR);
                move((j + 2) % 4, cubeR);
                temp1 = getEdge(cubeR);
                break;
            }
        }
        count = 0;
        for (int i = 0; i < 4; i++) {
            if (temp1.ed[i + 8][0] == side[i])
                count++;
        }
    }
    return;
}

void solver::random_moves(cube_r &cubeR) {
    for(int i = 0; i < 50; ++i) {
        move(rand() % 12, cubeR);
    }
}

void solver::print_scramble() {
    for(int i = 0; i < position; ++i) {
        std::cout << scramble[i];
    }
    std::cout << std::endl;
}

bool solver::evaluateCube(cube_r &cubeR) {
    for (int j = 0; j < 9; j++)
        if (cubeR.cube[0][j] != 'G')
            return false;
    for (int j = 0; j < 9; j++)
        if (cubeR.cube[1][j] != 'B')
            return false;
    for (int j = 0; j < 9; j++)
        if(cubeR.cube[2][j] != 'O')
            return false;
    for (int j = 0; j < 9; j++)
        if(cubeR.cube[3][j] != 'R')
            return false;
    for (int j = 0; j < 9; j++)
        if(cubeR.cube[4][j] != 'W')
            return false;
    for (int j = 0; j < 9; j++)
        if(cubeR.cube[5][j] != 'Y')
            return false;

    return true;
}



bool solver::check_invariant(cube_r &cubeR) {
    edge edges_cube = getEdge(cubeR);
    corner corners_cube = getCorner(cubeR);
    centre centers_cube = getCentre(cubeR);

    std::vector<std::string> good_corner;
    good_corner = {"RGY", "RGW", "RBW", "RBY", "OBW", "OBY", "OGW", "OGY"};
    bool flag = false;
    for (const auto& elem_str: good_corner) {
        flag = false;
        for (auto & corner : corners_cube.cor) {
            flag = flag || contains_corner(elem_str, corner);
        }
        if (!flag) {
            return false;
        }
    }

    std::vector<std::string> good_edge;
    good_edge = {"RB", "RW", "RG", "RY", "OB", "OW", "OG", "OY", "GY", "GW", "BY", "BW"};
    for (const auto& elem_str: good_edge) {
        flag = false;
        for (auto & edge : edges_cube.ed) {
            flag = flag || contains_edge(elem_str, edge);
        }
        if (!flag) {
            return false;
        }

    }

    std::vector<char> good_centre;
    good_centre = {'G', 'B', 'O', 'R', 'W', 'Y'};
    for (auto& elem_std: good_centre) {
        flag = false;
        for (auto& centre: centers_cube.centre) {
            if (centre == elem_std) {
                flag = true;
            }
        }
        if(!flag) {
            return false;
        }
    }


    return true;
}

bool solver::contains_corner(const std::string& str, const char corner[3]) {
    bool flag = false;
    for(int i = 0; i < 3; ++i) {
        flag = false;
        for(auto& ch: str) {
            if(ch == corner[i]) {
                flag = true;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return true;
}

bool solver::contains_edge(const std::string &str, const char edge[2]) {
    bool flag = false;
    for(int i = 0; i < 2; ++i) {
        flag = false;
        for(auto& ch: str) {
            if(ch == edge[i]) {
                flag = true;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return true;
}








