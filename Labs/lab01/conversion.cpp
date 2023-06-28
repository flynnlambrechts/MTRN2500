#include <iostream>

int main() {
    auto x{2};
    auto y{5};
    auto z{2.2};

    double result1{static_cast<double>(y / x)};
    double result2{static_cast<double>(y) / static_cast<double>(x)};
    double result3{static_cast<double>(static_cast<int>(z))};

    std::cout << result1 << std::endl;
    std::cout << result2 << std::endl;
    std::cout << result3 << std::endl;

    return 0;
}