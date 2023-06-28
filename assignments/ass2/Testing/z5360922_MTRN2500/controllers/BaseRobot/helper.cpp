#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "helper.hpp"

std::vector<std::vector<std::string>> readCSV(std::string name) {
    std::vector<std::vector<std::string>> data;
    std::ifstream ifst {"../../" + name};

    std::string row;
    std::getline(ifst, row);

    while(std::getline(ifst, row)) {
        std::stringstream ss(row);

        std::string rowContent{};
        std::vector<std::string> rowVec {};
        while (std::getline(ss, rowContent, ',')) {
            rowVec.push_back(rowContent);
        }
        data.push_back(rowVec);
    }
    return data;
}


std::vector<std::string> getRow(std::vector<std::vector<std::string>> &data, std::string title) {
    for (auto &row : data) {
        if (row.at(0) == title) {
            return row;
        }
    }
    return {};
}

double getBalance(const int id) {
    auto data {readCSV("Starting.csv")};
    return stod(getRow(data, std::to_string(id)).at(1));
}

std::vector<std::string> getMenuItem(std::string &name) {
    auto data {readCSV("Menu.csv")};
    return getRow(data, name);
}

double calcDist(const Position &p1, const Position &p2) {
    return std::sqrt(std::pow(p1.mX - p2.mX, 2) + std::pow(p1.mY - p2.mY, 2));
}

double calcAngleDiff(double facing, double bearing) {
    double angle {abs(facing - bearing)};
    return ((angle > M_PI) ? 2 * M_PI - angle : angle);
}

double getBearingToPosition(const Position &start, const Position &dest) {
    double dX = dest.mX - start.mX;
    double dY = dest.mY - start.mY;

    double acuteAngle {std::atan(dY / dX)};
    double bearing = (dX >= 0) ?  M_PI / 2 - acuteAngle : 3 * M_PI / 2  - acuteAngle;
    
    return bearing;
}