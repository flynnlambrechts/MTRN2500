#include <iomanip>
#include <iostream>

int main() {
    double nrows;
    std::cin >> nrows;

    for (double i {0}; i <= nrows; i++) {
        std::cout << std::setprecision(2) << std::fixed;
        std::cout << '[' << std::setw(i) << std::setfill('*') << ""
                  << std::setw(nrows - i) << std::setfill(' ') << "" << ']' 
                  << std::setw(7) << 100/nrows * i
                  << '%' << std::endl;
    }

}