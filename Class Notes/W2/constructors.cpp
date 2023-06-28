#include <iostream>

class Circle {
public:
    Circle() : mRadius{6.9}, mColour("Red") {};
    Circle(double radius, std::string colour) : mRadius(radius), mColour(colour) {}
    double getRadius();
    double getArea();
private:
    double mRadius {};
    std::string mColour {};
};

double Circle::getRadius() {
    return mRadius;
}

int main() {
    Circle circle {};
    std::cout << circle.getRadius() << '\n';
}