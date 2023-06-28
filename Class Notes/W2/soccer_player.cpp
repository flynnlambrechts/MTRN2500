#include <iostream>

class SoccerPlayer {
public:
    void run();
    void jump();
    void kickBall();
private:
    std::string mName;
    int mNumber;
    double mXLocation;
    double mYLocation; 
};

SoccerPlayer soccerPlayer;