#include <iostream>

namespace Gibberish {
    namespace MoreGibberish {
        int x {102};
    }
    namespace OtherGibberish {
        int y {42};
    }
    int z {36};
}

int main () {
    std::cout << Gibberish::MoreGibberish::x;
}