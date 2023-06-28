#include <iostream>

bool is_prime(int);

int main() {
    int input{0};
    int result{0};
    std::cin >> input;

    for (int i = 1; i <= input; i++) {
        if (is_prime(i)) {
            result += i;
        }
    }
    std::cout << result << std::endl;
}

bool is_prime(int n) {
    if (n == 0 || n == 1) { 
        return false;
    }
    for (int i = 2; i <= (n/2); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}