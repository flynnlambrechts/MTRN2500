#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include "z5360922StaffRobot.hpp"
#include "../BaseRobot/helper.hpp"

const std::string ACCOUNTPATH {"../../Account.csv"};

StaffRobot::StaffRobot() 
    : BaseRobot() {
        mKeyboard.enable(mSamplingPeriod);
    }

void StaffRobot::run() {

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

void StaffRobot::remoteControl() {
    int key {mKeyboard.getKey()};

    switch (key) {
        case webots::Keyboard::UP:
            moveForward();
            break;
        case webots::Keyboard::LEFT:
            turnLeft();
            break;
        case webots::Keyboard::DOWN:
            moveBackward();
            break;
        case webots::Keyboard::RIGHT:
            turnRight();
            break;
        case ' ':
            halt();
            break;
        case 'X':
        case webots::Keyboard::SHIFT+'X':
            mRemoteVelocity += 0.1 * mMotorMaxSpeed;
            mRemoteVelocity = (mRemoteVelocity > mMotorMaxSpeed) ? mMotorMaxSpeed : mRemoteVelocity;
            updateVelocityMagnitude();
            break;
        case 'Z':
        case webots::Keyboard::SHIFT+'Z':

            mRemoteVelocity -= 0.1 * mMotorMaxSpeed;
            mRemoteVelocity = (mRemoteVelocity < 0) ? 0 : mRemoteVelocity;
            updateVelocityMagnitude();
            break;
        case 'E':
        case webots::Keyboard::SHIFT+'E':
            mMode = modes::inital;
            mRemoteVelocity = mMotorMaxSpeed * 0.5;
            break;
    }
}

void StaffRobot::makeOrder(std::string order) {
    print("I am heading to order counter");
    move(orderCounter.first, orderCounter.second, M_PI);
    std::stringstream orderSS {order};
    
    int customer;
    std::string item {};
    
    orderSS >> customer;
    std::getline(orderSS, item, static_cast<char>(13));

    std::vector<std::string> orderDetails {getMenuItem(item)};

    std::stringstream printstream {};
    
    printstream << std::setprecision(2) << std::fixed;
    printstream << "Hi Customer " << customer << ", ";

    if (!orderDetails.empty()) {
        double price {stod(orderDetails.at(2))};
        printstream << "the price for " << item << " is " << price << " dollars";
        sendMessage(orderDetails.at(2) + " " + orderDetails.at(1), customer);
    } else {
        printstream << "oh no, we don't have " << item << " in our menu";
        sendMessage("Cancel", customer);
    }
    print(printstream.str());
    
    std::string message {waitForMessage()};
    double duration {};
    if (message == "Cancel") {

        print("I am returning to starting point");
        returnToStart();
        return;
    } else if (message == "Confirm") {
        duration = stod(orderDetails.at(1));
        printstream = {};
        printstream << "Thanks for your order. It will be ready in "
                    << duration << " seconds";
        print(printstream.str());
    }
    returnToStart();
    wait(duration * 1000);
    move(pickupCounter.first, pickupCounter.second, M_PI);
    print("Hi Customer " + std::to_string(customer) + ", your " + item + " is ready, please proceed to pickup counter");
    sendMessage("Complete", customer);

    waitForMessage();

    mBalance += stod(orderDetails.at(2));
    std::ofstream ofst (ACCOUNTPATH, std::ios_base::app);
    ofst << mOrderNumber << "," << item << "," << customer << "," << mBalance << std::endl;;
    mOrderNumber++;

    print("I am returning to starting point");
    returnToStart();
}


void StaffRobot::autoMode() {
    std::string message {waitForMessage()};
    std::stringstream account {};
    std::ofstream ofst (ACCOUNTPATH);
    ofst << "Order,Item,Customer,Account Balance ($)" << std::endl
         << mOrderNumber << ",,," << mBalance << std::endl;

    mOrderNumber++;
    while (message != "EXIT") {
        makeOrder(message);
        message = waitForMessage();
    }
    mMode = modes::inital;
}