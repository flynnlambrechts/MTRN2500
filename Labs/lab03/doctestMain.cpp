#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Complex.hpp"
// g++ -std=c++14  doctestMain.cpp -I doctest -o doctestMain


TEST_CASE("SImple test case which suceeds.") {
    int var1{42};
    int var2{42};
    CHECK(var1 == var2);
}

TEST_CASE("Complex number test") {
    mtrn2500::Complex x {3,4};
    mtrn2500::Complex y {3,4};
    CHECK(x.argument() == y.argument());
}

TEST_CASE("Complex modulus test") {
    mtrn2500::Complex x {3,4};
    double expected {5};
    CHECK(x.modulus() == expected);
}