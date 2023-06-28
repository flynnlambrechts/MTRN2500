#include <iostream>
#include <sstream>
#include <string>


int count_words(std::string const& sentence, std::string const& word) {
    std::stringstream ss {sentence};
    int count{0};
    std::string each_word;
    while (ss >> each_word) {
        if (each_word == word) {
            count++;
        }
    }
    return count;
}

int main() {
    std::string sentence, word;
    std::getline(std::cin, sentence);
    std::cin >> word;
    std::cout << count_words(sentence, word) << std::endl;
}
