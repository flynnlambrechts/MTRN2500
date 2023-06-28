#pragma once

#include "../BaseRobot/z5360922BaseRobot.hpp"

class CustomerRobot : public BaseRobot {
public:
    CustomerRobot();
    ~CustomerRobot() = default;

    virtual void run() override;
    virtual void remoteControl() override;
    virtual void autoMode() override;
private:
    static constexpr std::pair<double, double> orderCounter {0.375, 0.35};
    static constexpr std::pair<double, double> pickupCounter {-0.372, 0.35};

    void placeOrder(std::string order);

};