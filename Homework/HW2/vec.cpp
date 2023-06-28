#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec({-7,3,9,8});
    for (int i = 0; i<8; i++) {
        vec.push_back(i);
        if (i % 5 == 0) {
            vec.pop_back();
        }
    }

    std::cout << vec.size() << "\n";
}