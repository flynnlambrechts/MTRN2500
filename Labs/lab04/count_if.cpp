#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cin >> str;
    int count{0};

    count = std::count_if(str.begin(), str.end(), [](char &c){return std::isupper(c);});

    std::cout << count << std::endl;
}
