#include <iostream>

int main() {
    int *num_ptr {new int {3}};
    std::cout << "New int " << *num_ptr << " at location: " << num_ptr << "\n";
    delete num_ptr;
}