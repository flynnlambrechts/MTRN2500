#include <iostream>
#include <string>

class Shape {
public:
    std::string getColour() {return mColour;}
    void setColour(const std::string &colour) {mColour = colour;}
private:
    std::string mColour {};
};

class Circle : public Shape {
public:
    double getRadius() {return mRadius;}
    void setRadius(const double radius) {mRadius = radius;}
private:
    double mRadius {};
};

int main() {
    
    return 0;
}
