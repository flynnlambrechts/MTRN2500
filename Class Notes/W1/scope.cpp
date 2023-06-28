#include <iostream>

int a {0};

int main() {
    int b {1};

    {
        // c can only be accessed in these braces
        int c {2};
        std::cout << c << '\n';
    }

    std::cout << a << '\n';
    std::cout << b << '\n';

    int d {3};

    {
        // d has larger scope than these braces
        std::cout << d << '\n';
    }

    return 0;
}