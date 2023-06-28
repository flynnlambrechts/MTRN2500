#include <iostream>
// TODO: add additional headers if needed


// TODO: declare and implement base class
class Device {
public:
    Device(int battery = 60) : mBattery{battery} {}
    virtual void report() {
        std::cout << "My battery is at " << mBattery << "%!\n";
    }
    int mBattery;
};

// TODO: declare and implement derived class
class Laptop : public Device {
public:
    Laptop(int battery = 40) : Device(battery) {}
    virtual void report() {
        std::cout << "I'm calculating and my battery is at " << mBattery << "%!\n";
    }
    void operator~() {
        mBattery = 0;
        std::cout << "I'm running out of battery!";
    }
    friend std::istream& operator<<(std::istream& input, Laptop const& laptop);
};

std::istream& operator>>(std::istream& input, Laptop& laptop) {
    int charge{};
    input >> charge;
    laptop.mBattery += (charge);
    if (laptop.mBattery > 100) {
        int excess = laptop.mBattery -= 100;
        charge -= excess;
    }
    std::cout << "I've been charged by " << charge << "%!\n";
    return input;
}

int main() {
    Laptop laptop {0};
    std::cin >> laptop >> laptop;
    laptop.report();
}