#include <iostream>


namespace mtrn2500 {

class Triangle {
private:
    std::pair<double, double> p1 {};
    std::pair<double, double> p2 {};
    std::pair<double, double> p3 {};
public:
    Triangle(std::pair<double, double> const& p1, std::pair<double, double> const& p2, std::pair<double, double> const& p3)
        : p1{p1}, p2{p2}, p3{p3} {};

    Triangle(Triangle const& t)
        : p1{t.p1}, p2{t.p2}, p3{t.p3} {
            std::cout << "Copy constructing\n";
    }

    Triangle& operator=(Triangle const& t) {
        p1 = t.p1;
        p2 = t.p2;
        p3 = t.p3;
        std::cout << "Copy assigning\n";
        return *this;
    }

    std::pair<double, double> centroid() {
        double x = (p1.first + p2.first + p3.first)/3;
        double y = (p1.second + p2.second + p3.second)/3;
        return std::make_pair(x, y);
    }
};

}  // namespace mtrn2500

int main() {
    {
    mtrn2500::Triangle t({0, 0}, {0, 1}, {1, 1});
    auto p = t.centroid();
    std::cout << p.first << ", " << p.second << std::endl;
    }
    {
    mtrn2500::Triangle t({5.3, 1.5}, {-6.8, 6.3}, {-7.4, -8.1});
    auto p = t.centroid();
    std::cout << p.first << ", " << p.second << std::endl;
    }
}