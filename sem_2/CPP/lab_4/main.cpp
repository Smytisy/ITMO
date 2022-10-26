#include "solver.h"
#include <iostream>
#include <string>

using namespace std;


int main() {


    cube_r cubeR;
    cubeR.read_file();
    solver a;
    cout << a.check_invariant(cubeR) << endl;
    //cubeR.print();

//    std::cout << std::endl;
//    solver a;
//    cout << (a.evaluateCube(cubeR) ? "YES" : "NO") << endl;
//    a.random_moves(cubeR);
//    cout << (a.evaluateCube(cubeR) ? "YES" : "NO") << endl;
//    a.print_scramble();
//    //cubeR.print();
//
//    solver d(cubeR);
//    cout << (a.evaluateCube(cubeR) ? "YES" : "NO") << endl;
//    cubeR.print();
//d.print_scramble();

}