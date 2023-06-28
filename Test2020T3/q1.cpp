// TODO: Modify the 'Person' class as needed
#include <iostream> 
#include <string>

class Person {
public:
    Person(const std::string &name) : mName {name} {}
    virtual void reportName() = 0;
protected:
    std::string mName {};
};

// TODO: Declare and implement 'Student' class that inherits from 'Person'
class Student : public Person {
public:
    Student(const std::string &name) : Person(name) {}
    void reportName() {
        std::cout << "The person's name is " << mName << '\n';
    }
    void setName(std::string &name) {
        mName = name;
    }
    std::string getName() {
        return mName;
    }
private:
};

