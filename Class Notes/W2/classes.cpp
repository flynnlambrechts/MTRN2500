#include <iostream>

class Circle {
// can be accessed both inside and outside the class
public:
    // A consturctor is like the init from python
    // this is the structure defintion
    Circle(double radius, std::string colour);


    // // Can define function here if it is small
    // double getRadius() {
    //     return mRadius;
    // }

    double getRadius();
    double getArea();
    // bad practice to have public data members
    std::string mColour {};
// can only be accessed inside the class
private:
    // data memebers we use prefix m
    // can also use suffix underscore
    double mRadius {};
    // std::string mColour {};
};

// here is the constructor implementation
// this is not best practice you should use
// a member initialiser list
// see lecture slides
Circle::Circle(double radius, std::string colour = "Black") {
    mRadius = radius;
    mColour = colour;
}

// Recommended Way of implementing a class function
double Circle::getRadius() {
    return mRadius;
}

int main() {
    Circle circle {1.5, "Green"};
    // double a {circle.mRadius};
    double b {circle.getRadius()};

    std::cout << b << '\n';
    std::cout << circle.mColour << '\n';

    Circle circle1 {1};
    std::cout << circle1.mColour << " circle has radius " << circle.getRadius() << '\n';
    return 0;
}