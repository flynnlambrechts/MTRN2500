#include <iostream>

#include "helper.hpp"
#include "z5360922DirectorRobot.hpp"

const std::string commands {"Director: This is a simulation for MTRN2500 Cafe.\n"
                            "Director: Press [I] to reprint the commands.\n"
                            "Director: Press [R] to remote control a robot.\n"
                            "Director: Press [A] to enter the auto mode.\n"
                            "Director: Press [Q] to quit all controllers.\n"};

DirectorRobot::DirectorRobot()
    : mEmitter{*(getEmitter("emitter"))}
    , mReceiver{*(getReceiver("receiver"))} 
    , mKeyboard{*(getKeyboard())}
    , mOrders{getOrders()} {
    
    mReceiver.enable(mSamplingPeriod);
    mKeyboard.enable(mSamplingPeriod);
};

void DirectorRobot::run() {
    std::cout << commands;
    while (step(mSamplingPeriod) != -1) {
        const char key = std::toupper(static_cast<char>(mKeyboard.getKey()));

        switch (key) {
            case -1:
                break;
            case 'I':
                std::cout << commands;
                break;
            case 'R':
                setRemote();
                break;
            case 'A':
                autoMode();
                break;
            case 'Q':
                quitAll();
                wait(100);
                exit(0);
            default:
                print("Command not found.");
                std::cout << commands;
                break;
        }
    }
}

void DirectorRobot::sendMessage(const std::string& message, int robotID ) {
    mEmitter.setChannel(robotID);
    mEmitter.send(message.c_str(), message.size());
}

void DirectorRobot::sendToAll(const std::string &message) {
    for (int i {1}; i <= 5; i++) {
        sendMessage(message, i);
    }
}

std::string DirectorRobot::receiveMessage() {
    mReceiver.setChannel(6);

    std::string message {};
    
    if (mReceiver.getQueueLength() > 0) {
        message = static_cast<const char*>(mReceiver.getData());
        mReceiver.nextPacket();
    }
    return message;
}

void DirectorRobot::print(const std::string& message) {
    std::cout << "Director: " << message << '\n';
}

void DirectorRobot::wait(double duration) {
    const double start{getTime()};
    while (getTime() - start < duration * 0.001) {
        step(duration);
    }
}

void DirectorRobot::setRemote() {
    std::cout << "Director: Please select the robot to control remotely:\n"
                 "Director: Press [1] to control the Purple Robot (Customer1).\n"
                 "Director: Press [2] to control the White Robot (Customer2).\n"
                 "Director: Press [3] to control the Gold Robot (Customer3).\n"
                 "Director: Press [4] to control the Green Robot (Customer4).\n"
                 "Director: Press [5] to control the Black Robot (Staff).\n";
    
    int key = mKeyboard.getKey();
    key = std::toupper(static_cast<char>(key));
    while (key == -1) {
        this->step(mSamplingPeriod);
        key = mKeyboard.getKey();
    }
    key = key - int('0');

    if (key >= 1 && key <= 5) {
        sendMessage("R", key);
        while (mKeyboard.getKey() != 'E') {
            this->step(mSamplingPeriod);
        }
        print("Remote Control exited.");

    } else {
        print("Command not found.");
        std::cout << commands;
    }
}


void DirectorRobot::autoMode() {
    print("Auto Mode starts");
    for (int i {1}; i <= 5; i++) {
        sendMessage("A", i);
    }
    
    int counter {1};
    for (auto &order : mOrders) {
        sendMessage(order.second, order.first);

        while (receiveMessage() != "Done") {
            wait(mSamplingPeriod);
        }
        print("Order " + std::to_string(counter) + " complete");
        counter++;

    }
    print("All orders are completed");
    sendToAll("EXIT");
}

void DirectorRobot::quitAll() {
    sendToAll("Q");
}