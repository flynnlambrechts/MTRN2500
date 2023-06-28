#include <iostream>
#include <string>

int main() {
    char firstName[4] {"Leo"}; // the C way
    std::string lastName {"Wu"};  // the C++ way

    std::cout << "My name is " << firstName << "  " << lastName << "\n";

}