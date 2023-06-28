class Motor {
public:
    Motor() = default;
    Motor(double speed) : mSpeed{speed} {}
    double getSpeed() const {return mSpeed;};
    double setSpeed(double speed) {mSpeed = speed;};
private:
    double mSpeed;
};

class Machine {
public:
    Machine(Motor &motor) : mMotor{motor} {}
    double getMotorSpeed() const {return mMotor.getSpeed();}
    void setMotorSpeed(double speed) {mMotor.setSpeed(speed);}
private:
    Motor mMotor;
};