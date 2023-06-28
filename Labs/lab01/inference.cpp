
#include <iostream>

int main() {
    auto a{2};
    auto b{'b'};
    auto c{a * 0.1};
    auto d{static_cast<int>(c)};

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
}