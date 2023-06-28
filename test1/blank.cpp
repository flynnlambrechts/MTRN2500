#include <iostream>

class Robot {
public:
    static int Rcount;
    Robot() = default;

private:
    int mnum = {0};
};

int main() {
    int Robot::Rcount = 0;
    Robot robot1;
    Robot robot2;
    robot1.count++;
    std::cout << robot2.count <<std::endl;
    return 0;
}