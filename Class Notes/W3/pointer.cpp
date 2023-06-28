#include <iostream>

int num {88};
int *pNum {&num};

int main() {
    std::cout << "pNum: " <<  pNum << '\n';
    std::cout << "*pNum: " << *pNum << '\n';
}