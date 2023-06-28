#include <iostream>

class Circle {
public:
    Circle() : mRadius{6.9} {};
    double getRadius() const;
private:
    double mRadius {};
};

double Circle::getRadius() const {
    return mRadius;
}


int main() {
    Circle c1 {};
    std::cout << c1.getRadius();
}