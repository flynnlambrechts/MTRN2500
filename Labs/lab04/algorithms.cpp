#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

int main() {
    // Read in the vector size.
    int vec_size{0};
    std::cin >> vec_size;
    std::vector<int> vec(vec_size);

    // Read in the value.
    int value{0};
    std::cin >> value;

    // WRITE YOUR SOLUTION HERE.
    std::fill(vec.begin(), vec.end(), value);

    // To print the vector.
    for (auto const& i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
