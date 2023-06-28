#include <iostream>

int main() { 
    int myArray [3] {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        std::cout << myArray[i];
    }

    std::cout << '\n';

    for (int elem : myArray) {
        std::cout << elem;
    }
    std::cout << '\n';

    return 0;
}