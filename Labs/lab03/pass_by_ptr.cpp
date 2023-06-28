#include <memory>
#include <iostream>

void foo(std::shared_ptr<int> ptr) {
    std::cout << ptr << '\n';
    return;
}

int main() {
    auto ptr {std::make_shared<int>(42)};
    foo(ptr);
}
