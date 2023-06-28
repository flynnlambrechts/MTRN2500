#include <webots/Emitter.hpp>
#include <webots/Keyboard.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>

class DirectorRobot : public webots::Robot {
public:
    DirectorRobot();
    ~DirectorRobot() = default;

    void run();

    void sendMessage(const std::string&, int);
    std::string receiveMessage();

    void print(const std::string&);

private:
    static constexpr double mSamplingPeriod {128};
    
    webots::Emitter& mEmitter;
    webots::Receiver& mReceiver;
    webots::Keyboard& mKeyboard;

    std::vector<std::pair<int, std::string>> mOrders;

    void wait(double);
    void setRemote(); 
    void autoMode();
    void quitAll();
    void sendToAll(const std::string &message);
};