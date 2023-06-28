#include <string>
#include <iostream>

class Car {
public:
    Car(std::string name, double speed = 0.0) 
        : mName{name}, mSpeed{speed} {}
    
    Car& operator++() {

        mSpeed += 15.5;
        if (mSpeed > 60) {
            mSpeed = 60;
        }
        std::cout << mSpeed << std::endl;
        return *this;
    }
    Car& operator--() {

        mSpeed -= 15.5;
        if (mSpeed < 0) {
            mSpeed = 0;
        }

        return *this;
    }
    friend std::ostream& operator<<(std::ostream &os, Car &car);

private:
    std::string mName ={};
    double mSpeed;

};

std::ostream& operator<<(std::ostream &os, Car &car) {
    os << car.mName << " is running at speed " << car.mSpeed << "!\n";
    return os;
}

int main () {
    Car car1 {"Ford"};
    ++(--(++(--car1)));

    std::cout << car1;
}