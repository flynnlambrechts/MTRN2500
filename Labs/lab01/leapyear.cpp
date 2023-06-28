#include <iostream>

int main() {
    int year{0};
    bool is_leap_year{false};
    std::cin >> year;

    if (year >= 1582 && year%4 == 0 && ((year % 100 != 0) || (year % 100 == 0 && year % 400 == 0))) {
            is_leap_year = true;
    }

    std::cout << is_leap_year << std::endl;
}