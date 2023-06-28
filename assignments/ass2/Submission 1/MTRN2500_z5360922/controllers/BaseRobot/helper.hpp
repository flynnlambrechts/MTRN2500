#pragma once

#include <cmath>
#include <vector>

struct Position {
    Position() = default;
    Position(double x, double y, double heading = 0)
        : mX{x}, mY{y}, mHeading{heading} {};
    Position(std::pair<double, double> coords, double heading = 0) 
        : Position(coords.first, coords.second, heading) {};

    double mX;
    double mY;
    double mHeading;

    void operator()(double x, double y, double heading = 0) {
        mX = x;
        mY = y;
        mHeading = heading;
    }

    void operator()(std::pair<double, double> coords, double heading = 0) {
        operator()(coords.first, coords.second, heading);
    }
};

std::vector<std::vector<std::string>> readCSV(std::string name);

std::vector<std::string> getRow(std::vector<std::vector<std::string>> &data, std::string title);

double getBalance(const int id);

std::vector<std::string> getMenuItem(std::string &name);

double calcDist(const Position &p1, const Position &p2);

double calcAngleDiff(double facing, double bearing);

double getBearingToPosition(const Position &start, const Position &dest);