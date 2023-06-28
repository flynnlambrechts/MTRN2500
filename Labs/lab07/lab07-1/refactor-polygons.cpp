#include <cmath>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

class Polygon {
public:
    Polygon(std::vector<std::pair<double, double>> const& points) : mPoints(points) {}

    int numPoints() const { return mPoints.size(); }

    std::pair<double, double> centroid() const {
        return {linear_centroid(true), linear_centroid(false)};
    }
protected: 
    std::vector<std::pair<double, double>> mPoints;

private:
    double linear_centroid(bool x_or_y) const {
        return std::accumulate(
                   mPoints.begin(), mPoints.end(), 0.0,
                   [x_or_y](int i, auto const& j) { return x_or_y ? i + j.first : i + j.second; }) /
               numPoints();
    }
};


class Square : public Polygon {
public:
    Square(std::vector<std::pair<double, double>> const& points) : Polygon(points) {
        if (points.size() != 4) {
            throw std::invalid_argument("Invalid number of elements.");
        }
    }
};

class Triangle : public Polygon {
public:
    Triangle(std::vector<std::pair<double, double>> const& points) : Polygon(points) {
        if (points.size() != 3) {
            throw std::invalid_argument("Invalid number of elements.");
        }
    }

    double area() const {
        return 0.5 * std::abs(mPoints.at(0).first * (mPoints.at(1).second - mPoints.at(2).second) +
                              mPoints.at(1).first * (mPoints.at(2).second - mPoints.at(0).second) +
                              mPoints.at(2).first * (mPoints.at(0).second - mPoints.at(1).second));
    }
    
};

TEST_CASE("Square") {
    Square square({{0, 0}, {0, 1}, {1, 0}, {1, 1}});
    CHECK(square.numPoints() == 4);

    auto centre = square.centroid();
    CHECK(centre.first == doctest::Approx(0.5));
    CHECK(centre.second == doctest::Approx(0.5));
}

TEST_CASE("Triangle") {
    Triangle triangle({{0, 0}, {0, 1}, {1, 1}});
    CHECK(triangle.numPoints() == 3);

    auto centre = triangle.centroid();
    CHECK(centre.first == doctest::Approx(0.333333));
    CHECK(centre.second == doctest::Approx(0.666667));

    CHECK(triangle.area() == 0.5);
}