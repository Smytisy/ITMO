////
//// Created by mailo on 26.04.2022.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Polynomial.h"

TEST(Test_Polynom, Example_1) {
    Polynomial<3> pol = {4, -5, 1};
    EXPECT_EQ(pol.getPoint(2), -2);
}


TEST(Test_Polynom, Example_2) {
    Polynomial<3> pol = {1, 2, 3};
    EXPECT_EQ(pol.getPoint(2), 17);
}

