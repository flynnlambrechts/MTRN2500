#include <fstream>
#include <sstream>

#include "helper.hpp"

std::vector<std::pair<int, std::string>> getOrders() {
    std::vector<std::pair<int, std::string>> orders {};
    std::ifstream ifst {"../../Order.csv"};
    std::string line;
    std::getline(ifst, line);

    while (std::getline(ifst, line)) {
        std::stringstream ss(line);

        std::string num {};
        std::string order {};

        std::getline(ss, num, ',');
        std::getline(ss, order, ',');

        orders.push_back(std::make_pair(stoi(num), order));
    }
    
    return orders;
}
