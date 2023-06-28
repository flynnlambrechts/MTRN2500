#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::vector<std::pair<std::string, int>> vec{
        {"hello", 12382},
        {"apple", 2310},
        {"triangle", 814},
        {"world", 584},
        {"sentence", 9432},
    };
    std::vector<std::string> result1(vec.size());
    std::vector<int> result2(vec.size());

    std::transform(vec.begin(), vec.end(), result1.begin(), [](std::pair<std::string, int> i){return i.first;});
    std::transform(vec.begin(), vec.end(), result2.begin(), [](std::pair<std::string, int> i){return i.second;});

    // To print the results.
    for (auto const& i : result1) {
        std::cout << i << " " << std::endl;
    }
    std::cout << std::endl;

    for (auto const& i : result2) {
        std::cout << i << " " << std::endl;
    }
    std::cout << std::endl;
}
