// Replace Webot's provided main file with this because the former contains a lot of bad style.

#include <iostream>

// Remember to #include these files.
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>

constexpr int duration{64};  // Robot cycle duration.
constexpr double epuckMaxSpeed{6.28};

void wait(webots::Robot& robot, double waitPeriod) {
    const double start{robot.getTime()};
    while (robot.getTime() - start < waitPeriod * 0.001) {
        robot.step(duration);
    }
}

void moveForwards(webots::Motor& leftMotor, webots::Motor& rightMotor) {
    leftMotor.setPosition(INFINITY);
    rightMotor.setPosition(INFINITY);

    leftMotor.setVelocity(epuckMaxSpeed);
    rightMotor.setVelocity(epuckMaxSpeed);
}

void moveBackwards(webots::Motor& leftMotor, webots::Motor& rightMotor) {
    leftMotor.setPosition(INFINITY);
    rightMotor.setPosition(INFINITY);

    leftMotor.setVelocity(0.5 * -epuckMaxSpeed);
    rightMotor.setVelocity(0.5 * -epuckMaxSpeed);
}

void turnLeft(webots::Motor& leftMotor, webots::Motor& rightMotor) {
    leftMotor.setPosition(INFINITY);
    rightMotor.setPosition(INFINITY);

    leftMotor.setVelocity(0.5 * -epuckMaxSpeed);
    rightMotor.setVelocity(0.5 * epuckMaxSpeed);
}

void turnRight(webots::Motor& leftMotor, webots::Motor& rightMotor) {
    leftMotor.setPosition(INFINITY);
    rightMotor.setPosition(INFINITY);

    leftMotor.setVelocity(0.5 * epuckMaxSpeed);
    rightMotor.setVelocity(0.5 * -epuckMaxSpeed);
}


int main() {
    // Start with instantiating the controller for the robot.
    webots::Robot robot;

    // If we want to access the E-Puck's motor then we do this.
    //
    // Check the documentation for the names of the E-Puck devices:
    // https://cyberbotics.com/doc/guide/epuck
    //
    // The names of the motors are "left wheel motor" and "right wheel motor".
    //
    // Check the documentation for what devices we can get:
    // https://cyberbotics.com/doc/reference/robot?tab-language=c++#wb_robot_get_device
    //
    // The `getMotor()` function accepts a string for the name of a motor.
    auto leftMotorPtr{robot.getMotor("left wheel motor")};
    auto rightMotorPtr{robot.getMotor("right wheel motor")};

    // Check the documentation for how to use motor:
    // https://cyberbotics.com/doc/reference/motor?tab-language=c++
    std::cout << leftMotorPtr->getVelocity() << std::endl;
    std::cout << rightMotorPtr->getVelocity() << std::endl;

    // Instead of saving the motor as a pointer, we could also save it as a reference. This is
    // probably easier to use and pass around functions.
    webots::Motor& leftMotorRef{*robot.getMotor("left wheel motor")};
    webots::Motor& rightMotorRef{*robot.getMotor("right wheel motor")};

    std::cout << leftMotorRef.getVelocity() << std::endl;
    std::cout << rightMotorRef.getVelocity() << std::endl;

    // It is a good idea to set the initial velocity to 0 because we don't want an unexpected start.
    leftMotorRef.setVelocity(0);
    rightMotorRef.setVelocity(0);
    
    for (int i {0}; i < 100; i++) {
        moveForwards(leftMotorRef, rightMotorRef);
        wait(robot, 2048);
        turnRight(leftMotorRef, rightMotorRef);
        wait(robot, 1024);
    }
    
    // DO STUFF HERE.

}
