#include <iostream>
#include "Complex.hpp"

int main(int argc, char const *argv[]) {
    mtrn2500::Complex x{3, 4};
    mtrn2500::Complex y {x.conjugate()};
    std::cout << x.modulus() << "\n";
    std::cout << x.argument() << "\n";
    std::cout << y.argument() << "\n";
    return 0;
}