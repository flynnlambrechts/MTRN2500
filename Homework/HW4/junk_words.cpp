#include <iostream>
#include <sstream>
#include <string>
#include <map>

int count_junk_words(std::string const& sentence, std::string const& lexicon) {
    std::stringstream sentenceStream {sentence};
    std::stringstream lexiconStream {lexicon};
    std::map<std::string, bool> lexiconmap;

    std::string word;
    int count {0};

    while (lexiconStream >> word) {
        lexiconmap[word] = true;
    }

    while (sentenceStream >> word) {
        if (!lexiconmap[word]) {
            count++;
        }
    }


    return count;
}

int main() {
    std::string sentence {"hello world repetition"};
    std::string lexicon {"repetition repetition does not matter"};
    std::cout << count_junk_words(sentence, lexicon);

}