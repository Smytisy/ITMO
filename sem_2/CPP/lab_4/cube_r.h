#include <iostream>
#include <fstream>

class cube_r {
public:


    void read_file();

    cube_r();

    cube_r(const cube_r & toCpy);

    void print();


    void turn_clockwise(const cube_r& tmpCube, int side);

    void U();

    void Ui();

    void D();

    void Di();

    void F();

    void Fi();

    void B();

    void Bi();

    void L();

    void Li();

    void R();

    void Ri();



    char cube[6][10]{};
};