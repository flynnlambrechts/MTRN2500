#include <iostream>

int main() {
    auto a{123};
    auto b{2.1};
    auto c{b * 0.1};
    auto d{static_cast<char>(c) * b};
    auto e{static_cast<int>(a) * static_cast<char>(b)};
    auto f{static_cast<double>(c)};

    std::cout << typeid(a).name() << '\n';
    std::cout << typeid(b).name() << '\n';
    std::cout << typeid(c).name() << '\n';
    std::cout << typeid(d).name() << '\n';
    std::cout << typeid(e).name() << '\n';
    std::cout << typeid(f).name() << '\n';
}