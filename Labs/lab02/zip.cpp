#include <string>
#include <iostream>

int main () {
    std::string str1;
    std::string str2;
    std::string result {};

    std::cin >> str1;
    std::cin >> str2;

    int len = (str1.length() > str2.length()) ? str2.length() : len = str1.length();

    int i;
    for (i = 0; i < len; i++) {
        result += str1[i];
        result += str2[i];
    }
    
    result += str1.substr(i);
    result += str2.substr(i);
    
    std::cout << result << std::endl;
}