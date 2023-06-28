#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // Read in the vector size.
    int vec_size{0};
    std::cin >> vec_size;
    std::vector<int> vec(vec_size);

    // Read in the value.
    int value{0};
    std::cin >> value;

    // WRITE YOUR SOLUTION HERE.
    std::for_each(vec.begin(), vec.end(), [value](int &n){n = value;});
    std::for_each(vec.begin(), vec.end(), [](int &n){std::cout << n << ' ';});

    std::cout << std::endl;
}
