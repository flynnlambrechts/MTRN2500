#include <iostream>

// #define MAX        10;    // this is bad
constexpr int MAX {10};  //this is good
// allows type checking and allows for smaller scope
// easier to debug because has name for value

int main() {
    const int a {1};

    std::cout << "a is a const with value " << a << '\n';
    // ++a; //this will cause error

    int numApple {};
    double price {};
    std::string nameApple {};

    std::cout << "Please input the number of apples and their price and their name:\n";
    std::cin >> numApple >> price >> nameApple;

    std::cout << "Num apples is " << numApple << '\n';
    std::cout << "Cost is $" << price << '\n';
    std::cout << "Total cost is " << price * numApple << '\n';
    std::cout << "The name is " << nameApple << '\n';
}