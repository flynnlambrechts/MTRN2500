#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    std::string str;
    std::vector<std::string> vec;

    while (std::cin >> str) {
        vec.push_back(str);
    }

    std::map<std::string, int> fruit_counts;
    std::for_each(vec.begin(), vec.end(), [&fruit_counts](auto const& s){fruit_counts[s]++;});
    std::for_each(fruit_counts.begin(), fruit_counts.begin(), [](auto const& i){std::cout << i.first << ": " << i.second << "\n";});
}
