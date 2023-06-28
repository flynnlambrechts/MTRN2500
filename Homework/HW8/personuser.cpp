#include <string>

class Person {
public: 
    Person(std::string firstName, std::string lastName) 
        : mFirstName{firstName} ,mLastName{lastName} {}

    virtual std::string getName() const {
        return (mFirstName + " " + mLastName);
    }
protected:
    std::string mFirstName;
    std::string mLastName;

};

class User : public Person {
public:
    User(std::string firstName, std::string lastName) 
        : Person(firstName, lastName) {}
    
    std::string getName() const override {
        return (mLastName + " " + mFirstName);
    }
};