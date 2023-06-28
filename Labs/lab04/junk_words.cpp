#include <fstream>
#include <iostream>
#include <string>
#include <map>

int main() {
    std::ifstream lexicon_stream("lexicon.txt");
    
    std::string lexicon_word;
    std::map<std::string, bool> valid_words;
    while (lexicon_stream >> lexicon_word) {
        valid_words[lexicon_word] = true;
    }

    
    std::ifstream junk_stream("junk.txt");
    std::map<std::string, bool> junk_map;
    std::string junk_word;
    while (junk_stream >> junk_word) {
        junk_map[junk_word];
    }

    std::ofstream valid_stream("valid.txt");
    for (auto const& pair : junk_map) {
        if (valid_words.find(pair.first) != valid_words.end()) {
            valid_stream << pair.first << std::endl;
            std::cout << pair.first << std::endl;
        }
    }
}