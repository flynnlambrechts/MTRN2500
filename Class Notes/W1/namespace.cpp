#include <iostream>

namespace mtrn2500 {
    int numLecturers {2};
}

namespace mtrn4110 {
    int numLecturers {1};
}

int main() {
    std::cout << "Number of lecturers in mtrn2500: " << mtrn2500::numLecturers << '\n';
    std::cout << "Number of lecturers in mtrn4110: " << mtrn4110::numLecturers << '\n';

    // we can set the name space to avoid declaring it each call
    using namespace mtrn2500;
    std::cout << "Number of lecturers: " << numLecturers << '\n';

    return 0;
}