#include <iostream>

class Cents {
public:
    Cents(int cents)
        : mCents { cents } {
        }
    
    friend Cents operator+ (const Cents &lhs, const Cents &rhs);
    friend std::ostream& operator<< (std::ostream &out, const Cents &cents);
private:
    int mCents {};
};

Cents operator+ (const Cents &lhs, const Cents &rhs) {
    return Cents(lhs.mCents + rhs.mCents);
}

std::ostream& operator<< (std::ostream &out, const Cents &cents) {
    out << cents.mCents << "c";
    return out;
}

int main() {
    Cents cents1 {1};
    Cents cents2 {2};
    Cents sum {cents1 + cents2};

    std::cout << sum << '\n';

}