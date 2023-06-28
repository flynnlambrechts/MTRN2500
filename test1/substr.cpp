#include <sstream>
#include <iostream>
#include <string>

int main() {
    std::stringstream ss {"UNSW-MTRN\nhello"};
    std::string subStr;
    std::getline(ss, subStr);
    std::getline(ss, subStr, '-');
    std::cout << subStr;
}