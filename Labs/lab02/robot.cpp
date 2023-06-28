#include <iostream>
#include <string>

// constexpr unsigned proximity_sensors{0b1000};
// constexpr unsigned lidar{0b0100};
// constexpr unsigned motors{0b0010};
// constexpr unsigned encoders{0b0011};

enum class Robot : unsigned {
    lidar = 0b0100,
    proximity_sensors = 0b1000,
    encoders = 0b0011,
    motors = 0b0010,
};

void turn_on_devices(unsigned devices) {
    if (devices & static_cast<int>(Robot::proximity_sensors)) {
        std::cout << "Turning on proximity sensors..." << std::endl;
    }
    if (devices & static_cast<int>(Robot::lidar)) {
        std::cout << "Turning on lidar..." << std::endl;
    }
    if (devices & static_cast<int>(Robot::encoders)) {
        std::cout << "Turning on encoders..." << std::endl;
    }
    if (devices & static_cast<int>(Robot::motors)) {
        std::cout << "Turning on motors..." << std::endl;
    }
}

int main() {
    std::string devices{"0000"};
    std::cin >> devices;
    turn_on_devices(std::stoi(devices, 0, 2));
}
