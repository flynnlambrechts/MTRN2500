#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>


void solution(std::string const& input) {
    std::map<int, bool> vec;
    std::stringstream num_stream {input};
    int num;
    
    while (num_stream >> num) {
        if (!vec[num]) {
            vec[num] = true;
        }
        
    }

    
    std::sort(vec.begin(), vec.end(), std::greater<>());
    for (auto &elem : vec) {
        std::cout << elem.first << " ";
    }
    std::cout << '\n';
    
}

int main() {
    solution("1 2 3 4");
    return 0;
}