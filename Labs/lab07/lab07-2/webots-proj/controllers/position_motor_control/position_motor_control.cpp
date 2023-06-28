// Replace Webot's provided main file with this because the former contains a lot of bad style.

#include <iostream>

// Remember to #include these files.
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/PositionSensor.hpp>

constexpr double radius{0.0205};
// constexpr double axel{0.052};
constexpr int duration{64};  // Robot cycle duration.
constexpr double moveForwardRotation{0.5 / radius};



void wait(webots::Robot& robot, double waitPeriod) {
    const double start{robot.getTime()};
    while (robot.getTime() - start < waitPeriod * 0.001) {
        robot.step(duration);
    }
}

void halt(webots::Motor& leftMotor, webots::Motor& rightMotor);

// void moveForward(webots::Motor& leftMotor, webots::Motor& rightMotor) {
//     leftMotor.setPosition(moveForwardRotation);
//     rightMotor.setPosition(moveForwardRotation);


//     leftMotor.setVelocity(6.28);
//     rightMotor.setVelocity(6.28);
// }

void moveForward(webots::Motor& leftMotor, webots::Motor& rightMotor,
                 webots::PositionSensor& leftSensor, webots::PositionSensor& rightSensor) {
    double leftCur = leftSensor.getValue();
    double rightCur = rightSensor.getValue();       

    leftMotor.setPosition(leftCur + moveForwardRotation);
    rightMotor.setPosition(rightCur + moveForwardRotation);     

    leftMotor.setVelocity(6.28);
    rightMotor.setVelocity(6.28);    
}

// void moveBackward(webots::Motor& leftMotor, webots::Motor& rightMotor,
//                   webots::PositionSensor& leftSensor, webots::PositionSensor& rightSensor);

// void turnRight(webots::Motor& leftMotor, webots::Motor& rightMotor,
//                webots::PositionSensor& leftSensor, webots::PositionSensor& rightSensor);

int main() {
    webots::Robot controller;
    webots::Motor& leftMotor{*controller.getMotor("left wheel motor")};
    webots::Motor& rightMotor{*controller.getMotor("right wheel motor")};

    webots::PositionSensor leftPos{*controller.getPositionSensor("left wheel sensor")};
    webots::PositionSensor rightPos{*controller.getPositionSensor("right wheel sensor")};

    leftPos.enable(duration);
    rightPos.enable(duration);

    halt(leftMotor, rightMotor);

    // moveForward(leftMotor, rightMotor);

    moveForward(leftMotor, rightMotor, leftPos, rightPos);

    // DO STUFF HERE.
}
