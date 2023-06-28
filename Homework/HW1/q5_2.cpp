#include <iostream>

int main() {
    int n;
    std::cin >> n;
    for (int i {1}; i <= 30; i += 3) {
        if (i > n) {
            std::cout << ">";
        } else if (i % 2 != 0) {
            std::cout << "Odd";
        } else {
            std::cout << i;
        }
        
        if (i != 28) {
            std::cout << ", ";
        }
    }
}