#include <iostream>
#include <set>

int main() {
    std::set<double> s{0.2, 1.41, 12.2, 43.3};
    std::set<double>::iterator it_set;

    for (it_set = s.begin(); it_set != s.end(); it_set++) {
        std::cout << *it_set << '\n';
    }
}
