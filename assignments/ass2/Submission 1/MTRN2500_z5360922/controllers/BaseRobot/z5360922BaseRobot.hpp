#pragma once

#include <unordered_map>

#include <webots/Compass.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Emitter.hpp>
#include <webots/GPS.hpp>
#include <webots/Keyboard.hpp>
#include <webots/Motor.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>

#include "helper.hpp"

class BaseRobot : public webots::Robot {
public:
    BaseRobot();
    ~BaseRobot();

    void move(double x, double y, double heading);

    void sendMessage(const std::string&, int);

    std::string receiveMessage();

    friend std::ostream& operator<<(std::ostream& os, BaseRobot const&);

    virtual void run() = 0;

    virtual void remoteControl() = 0;

    virtual void autoMode() = 0;
protected:
    int mID;
    static constexpr double mSamplingPeriod {64};
    static constexpr double mMotorMaxSpeed {6.28};

    int mMode;
    double mBalance;
    double mRemoteVelocity;
    Position mStartPos;

    enum modes {inital, remote, autom};
    enum IDs {C1 = 1, C2, C3, C4, SR, DR};
    std::unordered_map<std::string, int> getID {
        {"Customer1", IDs{C1}},
        {"Customer2", IDs{C2}},
        {"Customer3", IDs{C3}},
        {"Customer4", IDs{C4}},
        {"Staff", IDs{SR}},
        {"Director", IDs{DR}}
    };

    webots::Motor& mLeftMotor;
    webots::Motor& mRightMotor;
    webots::Keyboard& mKeyboard;

    void wait(double duration);

    void halt() {
        mLeftMotor.setPosition(INFINITY);
        mRightMotor.setPosition(INFINITY);
        mLeftMotor.setVelocity(0);
        mRightMotor.setVelocity(0);
    }

    void handleMessage(std::string message);

    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void returnToStart();

    void updateVelocityMagnitude();
    std::string waitForMessage();

    void print(std::string message);

private:
    static constexpr double mWheelRadius {0.0206};
    static constexpr double mAxelLength {0.052};

    webots::Emitter& mEmitter;
    webots::Receiver& mReceiver;
    webots::GPS& mGPS;
    webots::Compass& mCompass;
    webots::DistanceSensor& mLeftEye;
    webots::DistanceSensor& mRightEye;
    webots::PositionSensor& mLeftWheelSensor;
    webots::PositionSensor& mRightWheelSensor;
    

    // Helpers

    void setVelocity(double, double);

    Position getCurrentPos() const {
        const double *currentPos {mGPS.getValues()};
        return Position(currentPos[2], currentPos[0], getCurrentBearing());
    }

    double getCurrentBearing() const {
        const double *north = mCompass.getValues();
        double rad = atan2(north[0], north[2]);
        double bearing = (rad - M_PI);
        if (bearing < 0.0) {
            bearing = bearing + 2 * M_PI;
        }
        return bearing;
    }
    
    void faceBearing(double);
};