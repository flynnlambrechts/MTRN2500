#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>

int main() {
    std::map<int, std::string> student_record {
        {520000, "Jane"},
        {511111, "Peter"},
    };

    std::cout << student_record[520000] << std::endl;

    std::queue<std:string> knockout_queue;
    knockout_queue.push("Anton");
    knockout_queue.push("Nicole");
    std::string front_of_queue = knockout_queue.front();
    k
}

