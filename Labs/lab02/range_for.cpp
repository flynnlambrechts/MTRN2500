#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec{10, -10, 9, 9};

    // WRITE YOUR SOLUTION HERE.
    int sum {0};
    for (int &elem : vec) {
        sum += elem;
        elem = sum;
    }

    // To print the vector.
    for (auto const& i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
