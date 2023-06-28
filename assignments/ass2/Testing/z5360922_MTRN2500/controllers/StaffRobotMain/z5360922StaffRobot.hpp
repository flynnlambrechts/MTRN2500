#pragma once

#include <string>

#include "../BaseRobot/z5360922BaseRobot.hpp"

class StaffRobot : public BaseRobot {
public:
    StaffRobot();
    ~StaffRobot() = default;

    virtual void run() override;
    virtual void remoteControl() override;
    virtual void autoMode() override;
private:
    int mOrderNumber {};
    static constexpr std::pair<double, double> orderCounter {0.375, 0.87};
    static constexpr std::pair<double, double> pickupCounter {-0.372, 0.87};

    void makeOrder(std::string);
};
