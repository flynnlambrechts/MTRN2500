#include <iostream>

int main() {
    std::string in_str {};
    std::cin >> in_str;
    
    bool upper = true;
    for (char elem : in_str) {
        if (isupper(elem) == 0) {
            upper = false;
        }
    }
    if (upper == true) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}