#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> ptr1 {std::make_unique<int>(1)};
    std::shared_ptr<int> ptr2 {std::make_shared<int>(2)};
    std::shared_ptr<int> ptr3 {ptr2};
    int var{5};

    std::unique_ptr<int> ptr4 {std::make_unique<int>(var)};
    std::unique_ptr<int> ptr5 {std::make_unique<int>(var)};

    std::cout << ptr1 << ' ' << *ptr1 << '\n';
    std::cout << ptr2 << ' ' << *ptr2 << '\n';
    std::cout << ptr5 << ' ' << *ptr5 << '\n';
    std::cout << ptr3 << ' ' << *ptr3 << '\n';
    std::cout << ptr4 << ' ' << *ptr4 << '\n';

    

}
