#include <iomanip>
#include <iostream>

#include "helper.hpp"
#include "z5360922BaseRobot.hpp"

BaseRobot::BaseRobot()
    : mMode{modes::inital}
    , mRemoteVelocity{0.5 * mMotorMaxSpeed}
    , mLeftMotor{*(getMotor("left wheel motor"))}
    , mRightMotor{*(getMotor("right wheel motor"))}
    , mKeyboard{*(getKeyboard())}
    , mEmitter{*(getEmitter("emitter"))}
    , mReceiver{*(getReceiver("receiver"))}
    , mGPS{*(getGPS("gps"))}
    , mCompass{*(getCompass("compass"))}
    , mLeftEye{*(getDistanceSensor("left eye"))}
    , mRightEye{*(getDistanceSensor("right eye"))}
    , mLeftWheelSensor{*(getPositionSensor("left wheel sensor"))} 
    , mRightWheelSensor{*(getPositionSensor("right wheel sensor"))} {
        halt();

        mLeftWheelSensor.enable(mSamplingPeriod);
        mRightWheelSensor.enable(mSamplingPeriod);
        mCompass.enable(mSamplingPeriod);
        mGPS.enable(mSamplingPeriod);
        mReceiver.enable(mSamplingPeriod);

        wait(500);

        mID = getID[getName()];
        mBalance = getBalance(mID);
        mStartPos = getCurrentPos();

        std::cout << "Robot " << mID << " has been created.\n";
}

BaseRobot::~BaseRobot() = default;

void BaseRobot::wait(double duration) {
    const double start{getTime()};
    while (getTime() - start < duration * 0.001) {
        step(duration);
    }
}

int rightOrLeft(double facing, double bearing) {
    enum leftRight {left = -1, right = 1};
    double diff{facing - bearing};

    if ((diff > 0 && diff > M_PI) || (diff < 0 && diff > -M_PI)) {
        return leftRight::right;
    } else if ((diff > 0 && diff < M_PI) || (diff < 0 && diff <= -M_PI)) {
        return leftRight::left;
    }
    
    return 1;
}

void BaseRobot::faceBearing(const double bearing) {
    // Accurate to a third of a degree
    const double EPS = M_PI / 720;
    const double slowingAngle {M_PI / 36};

    double currentBearing {getCurrentBearing()};
    double turnDist {calcAngleDiff(currentBearing,  bearing)};

    double velocity = rightOrLeft(currentBearing, bearing) * (mMotorMaxSpeed / 4);

    setVelocity(velocity, -velocity);
    
    bool reversed {false};
    int reversedCount {0};

    while (turnDist > EPS && reversedCount < 10) {
        this->step(mSamplingPeriod);
        double prevTurnDist {turnDist};
        turnDist = calcAngleDiff(getCurrentBearing(),  bearing);
        if (turnDist < slowingAngle) {
            velocity = (abs(velocity) >= 0.1 * mMotorMaxSpeed) ? velocity * 0.25 : velocity;
        }
        if (prevTurnDist < turnDist) {
            reversed = !reversed;
            reversedCount++;
            velocity = (abs(velocity) >= 0.01 * mMotorMaxSpeed) ? velocity * 0.25 : velocity;
        }
        setVelocity((!reversed*2 - 1) * velocity, (!reversed*2 - 1) * -velocity);
    }
    halt();
}

void BaseRobot::move(double x, double y, double heading) {
    const double slowingDistance {0.1};
    const double EPS {0.01};

    Position currentPos {getCurrentPos()};
    Position dest(x, y, heading);

    double dist {calcDist(currentPos, dest)};

    while (dist > EPS) {
        faceBearing(getBearingToPosition(getCurrentPos(), dest));

        Position startingPoint(getCurrentPos());

        while (calcDist(getCurrentPos(), startingPoint) < dist) {
            double distToGo {calcDist(getCurrentPos(), dest)};
            double velocity = (distToGo > slowingDistance) ? mMotorMaxSpeed : mMotorMaxSpeed * (distToGo / slowingDistance);
            setVelocity(velocity, velocity);
            this->step(mSamplingPeriod);
        }
        halt();
    
        dist = calcDist(getCurrentPos(), dest);
    };

    faceBearing(dest.mHeading);
    halt();
    wait(1000);
}

void BaseRobot::sendMessage(const std::string& message, int robotID) {
    mEmitter.setChannel(robotID);
    mEmitter.send(message.c_str(), message.size());
}

std::string BaseRobot::receiveMessage() {
    mReceiver.setChannel(mID);
    std::string message {};
    
    if (mReceiver.getQueueLength() > 0) {
        message = static_cast<const char*>(mReceiver.getData());
        mReceiver.nextPacket();
    }
    return message;
}

std::ostream& operator<<(std::ostream& os, BaseRobot const& robot) {
    Position position {robot.getCurrentPos()};
    std::cout << std::setprecision(3) << std::fixed;
    os << "The robot " << robot.mID << " is currently at ["
       << position.mX << ", "
       << position.mY << "] facing " << position.mHeading
       << ".\n";
    return os;
}

void BaseRobot::handleMessage(std::string message) {
    if (message == "R") {
        mMode = modes::remote;
    } else if (message == "A") {
        mMode = modes::autom;
    } else if (message == "Q") {
        exit(0);
    }
}

void BaseRobot::setVelocity(double leftVelocity, double rightVelocity) {
    mLeftMotor.setPosition(INFINITY);
    mRightMotor.setPosition(INFINITY);
    mLeftMotor.setVelocity(leftVelocity);
    mRightMotor.setVelocity(rightVelocity);
}

void BaseRobot::moveForward() {
    setVelocity(mRemoteVelocity, mRemoteVelocity);
}

void BaseRobot::moveBackward() {
    setVelocity(-mRemoteVelocity, -mRemoteVelocity);
}

void BaseRobot::turnLeft() {
    setVelocity(-mRemoteVelocity / 2, mRemoteVelocity / 2);
}

void BaseRobot::turnRight() {
    setVelocity(mRemoteVelocity / 2, -mRemoteVelocity / 2);
}

void BaseRobot::returnToStart() {
    move(mStartPos.mX, mStartPos.mY, mStartPos.mHeading);
}

void BaseRobot::updateVelocityMagnitude() {
    int rightDirec = {(mRightMotor.getVelocity() >= 0) * 2 - 1};
    int leftDirec = {(mLeftMotor.getVelocity() >= 0) * 2 - 1};
    setVelocity(mRemoteVelocity * leftDirec, mRemoteVelocity * rightDirec);
}

std::string BaseRobot::waitForMessage() {
    while (step(mSamplingPeriod) != -1) {
        std::string message {receiveMessage()};
        if (message != "") {
            return message;
        }
    }
    return "";   
}

void BaseRobot::print(std::string message) {
    std::string title;
    if (mID == 5) {
        title = "Staff";
    } else {
        title = "Customer " + std::to_string(mID);
    }
    
    std::cout << title << ": " << message << '\n';
}