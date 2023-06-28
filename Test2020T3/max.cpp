#include <iostream>
#include <vector>

int findMax(std::vector<int> &vec) {
    int max = vec.at(0);
    for (int &elem : vec) {
        if (elem > max) {
            max = elem;
        }
    }
    return max;
}

void print(int n) {
    std::cout << n <<'\n';
}

int main() {
    std::vector<int> vec {0, 1, 2};
    print(findMax(vec));
}