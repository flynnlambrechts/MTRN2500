#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1 {1, 2, 3};
    v1.push_back(4);
    for (auto i : v1) {
        std::cout << i;
    }
    std::cout << '\n';
    return 0;
}