#include <iostream>

int main(void) {
    for (int i = 0; i < 100; i++) {
        if (i % 3 == 0) {
            std::cout << i << '\n';
        }
    }
}