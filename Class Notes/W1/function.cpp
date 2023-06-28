#include <iostream>

int fun1(int = 1, int = 2, int = 3);
int fun2(int, int, int = 3);

void print(int number) {
    std::cout << number << '\n';
}

void print(std::string word) {
    std::cout << word << '\n';
}

int fun3(int n1) {
    return n1 * 2;
}

int main() {
    std::cout << fun1(4,5,6) << '\n';
    std::cout << fun1(4,5) << '\n';
    std::cout << fun1(4) << '\n';
    std::cout << fun1() << '\n';

    std::cout << fun2(1, 2, 4) << '\n';
    std::cout << fun2(1, 2) << '\n';

    std::cout << fun3(1) << '\n';
    // function overloading is allowed
    // it will know which to used based on
    // parameter types
    print(3);
    print("three");

    return 0;
}



int fun1(int n1, int n2, int n3) {
    return n1 + n2 + n3;
}

int fun2(int n1, int n2, int n3) {
    return n1 + n2 + n3;
}