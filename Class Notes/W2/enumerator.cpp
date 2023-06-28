#include <iostream>

constexpr int OCTOBER {10};

enum class Month {
    Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

Month selectMonth() {
    return Month::Oct;
}

int main() {
    Month month {selectMonth()};

    if (month == Month::Oct) {
        std::cout << " The month is october!\n";
    }

    return 0;
}