#include <iostream>

void print(int input) { std::cout << input << std::endl; }
void print(double input) { std::cout << input << std::endl; }
void print(char input) { std::cout << input << std::endl; }

int main() {
    print(42);
    print(42.2);
    print('a');
}