#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec {1, 2, 3};

    for (auto &i : vec) {
        std::cout << &i << '\n';
    }
    vec.push_back(4);
    std::cout << &vec[3] << '\n';

    vec.push_back(5);
    std::cout << &vec[4] << '\n';
}