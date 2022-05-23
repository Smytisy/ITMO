#include <iostream>
#include "Polynomial.h"
#include "gtest/gtest.h"
#include "delete.cpp"

template<int value>
struct Check_pol {
    int result = value;
};


int main() {
    constexpr Polynomial<3> pol ({4, -5, 1}) ;
    pol.getPoint(2);

    Check_pol<pol.getPoint(2)> p_test;

    std::cout << pol << std::endl;
    std::cout << p_test.result;


    return RUN_ALL_TESTS();
}
