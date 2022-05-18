#include <iostream>


#include "Polynomial.h"
#include "Figures.cpp"

int main() {
    Triangle trian = {Point(1, 2), Point(5, 10), Point(3, -6)};


    RegPolygon regpol = RegPolygon(3, {Point(5, 5), Point(1, 2)});
    RegPolygon repol2 = regpol;


    //std::cout << trian.Perimeter() << std::endl;


    regpol = RegPolygon(6, {Point(5, 5), Point(-3, 5)});


    //std::cout << regpol.Perimeter() << std::endl;
    //std::cout << repol2.Perimeter() << std::endl << std::endl;

    //std::cout << trian.Area() << std::endl;



    //Polygon polygon = {Point(0, 0), Point(1, 1), Point(2, 3)};
    //std::cout << (polygon.checkPolygon() ? "YES" : "NO") << std::endl;



/*
    Polynomial afaf = {{1, 2},
                       {2, 3},
                       {3, 5}};

    Polynomial dafdaf = {{1, 2}, {2, 5}, {4, 1}};
    afaf.Print();
    dafdaf.Print();
    dafdaf = afaf + dafdaf;
    dafdaf.Print();
    */


    Polynomial multi_1 = {{2, 1},
                          {0, 4}};
    Polynomial multi_2 = {{1, 3},
                          {3, 1}};
    multi_1.Print();
    multi_2.Print();
    multi_1 = multi_1 * multi_2;
    multi_1.Print();

    multi_1 *= multi_2;
    multi_1.Print();

    multi_1 -= multi_2;
    multi_1.Print();

    multi_1 /= 5;
    multi_1.Print();

    multi_1 *= 5;
    multi_1.Print();

    multi_1.Derivative();
    multi_1.Print();

    std::cout << multi_1;

    Polynomial kol;
    std::cin >> kol;
    std::cout << kol;
    std::cout << kol[2] << std::endl;




    return 0;
}
