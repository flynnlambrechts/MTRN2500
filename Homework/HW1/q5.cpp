#include <iostream>

int main() {
    int a {};
    std::cin >> a;
    for (int i {10}; i > 0; --i) {
        if (i % a == 0) {
            std::cout << "Multiple";
        } else if (i % 2 == 0) {
            std::cout << "Even";
        } else {
            std::cout << i;
        }

        if (i != 1) {
            std::cout << ", ";
        }
    }
}