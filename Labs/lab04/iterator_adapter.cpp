#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // Read in n.
    int n{0};
    std::cin >> n;

    // Read in the vector.
    int i{0};
    std::vector<int> vec;
    while (std::cin >> i) {
        vec.push_back(i);
    }

    auto max_value = std::max_element(vec.begin(), vec.end());
    if (max_value == vec.end()) {
        throw std::out_of_range("No! Out of range.");
    }

    std::fill_n(std::back_inserter(vec), n, *max_value);

    // To print the vector.
    for (auto const& i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
