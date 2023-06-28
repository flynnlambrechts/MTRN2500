#include <iostream>

int main() {
    std::string in_str {};
    std::cin >> in_str;

    std::string rev_str {};
    int len  = in_str.length();
    for (int i {len - 1}; i >= 0; i--) {
        rev_str.push_back(in_str[i]);
    }

    if (in_str == rev_str) {
        std::cout << "YES" << "\n";
    } else {
        std::cout << "NO" << "\n";
    }
}