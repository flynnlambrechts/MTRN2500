


#include <iostream>

// only need to declare if function is define after where it is used
// bad practice to put functions before main though
void d_cmp(int);

const int threshold{3};  // metres.

int main() {
    int distance1 {2};  // metres
    int distance2 {3};  // metres.
    int distance3 {4};  // metres.
    
    d_cmp(distance1);
    d_cmp(distance2);
    d_cmp(distance3);
}

void d_cmp(int dist) {
    bool is_close {false};
    if (dist < threshold) {
        is_close = true;
    }
    std::cout << is_close << std::endl;
}