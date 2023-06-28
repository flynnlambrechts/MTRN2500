#include <cctype>
#include <iomanip>
#include <sstream>

#include "z5360922CustomerRobot.hpp"

CustomerRobot::CustomerRobot() 
    : BaseRobot() {
        mKeyboard.enable(mSamplingPeriod);
    }

void CustomerRobot::run() {
    while (step(mSamplingPeriod) != -1) {
        std::string message {receiveMessage()};

        handleMessage(message);

        if (mMode == modes::remote) {
            remoteControl();
        } else if (mMode == modes::autom) {
            autoMode();
        }   
        
    }
}

void CustomerRobot::remoteControl() {
    char key = std::toupper(static_cast<char>(mKeyboard.getKey()));
    
    switch (key) {
        case 'W':
            moveForward();
            break;
        case 'A':
            turnLeft();
            break;
        case 'S':
            moveBackward();
            break;
        case 'D':
            turnRight();
            break;
        case ' ':
            halt();
            break;
        case 'X':
            mRemoteVelocity += 0.1 * mMotorMaxSpeed;
            mRemoteVelocity = (mRemoteVelocity > mMotorMaxSpeed) ? mMotorMaxSpeed : mRemoteVelocity;
            updateVelocityMagnitude();
            break;
        case 'Z':
            mRemoteVelocity -= 0.1 * mMotorMaxSpeed;
            mRemoteVelocity = (mRemoteVelocity < 0) ? 0 : mRemoteVelocity;
            updateVelocityMagnitude();
            break;
        case 'E':
            mMode = modes::inital;
            mRemoteVelocity = mMotorMaxSpeed * 0.5;
            break;
    }
}

void CustomerRobot::placeOrder(std::string order) {
    print("I am heading to order counter");
    move(orderCounter.first, orderCounter.second, 0);

    print("Hi Staff, I want to order " + order);
    sendMessage(std::to_string(mID) + order, getID["Staff"]);

    std::string message {waitForMessage()};

    if (message == "Cancel") {
        print("Oops, I will cancel the order");
        print("I am returning to starting point");
        sendMessage("Cancel", getID["Staff"]);
        returnToStart();
        sendMessage("Done", getID["Director"]);
        return;
    }
    double cost;
    std::stringstream receiveStream {message};
    receiveStream >> cost;
    if (cost > mBalance) {
        print("Oops, I can't afford it. I will cancel the order");
        sendMessage("Cancel", getID["Staff"]);
        returnToStart();
        sendMessage("Done", getID["Director"]);
        return;
    } else {
        mBalance -= cost;
        print("Hi Staff, I will buy it");
        sendMessage("Confirm", getID["Staff"]);
        move(0, 0, 0);
    }
    waitForMessage();
    print("I am heading to pickup counter");
    move(pickupCounter.first, pickupCounter.second, 0);
    print("I got my " + order);
    print("I am returning to starting point");
    sendMessage("Collected", getID["Staff"]);
    returnToStart();
    sendMessage("Done", getID["Director"]);
}

void CustomerRobot::autoMode() {
    std::string message {waitForMessage()};
    while (message != "EXIT") {
        placeOrder(message);
        message = waitForMessage();
    }
    std::stringstream sst {};
    sst << std::setprecision(2) << std::fixed;
    sst << "My current balance is " << mBalance <<  " dollars";
    print(sst.str());
    mMode = modes::inital;
}