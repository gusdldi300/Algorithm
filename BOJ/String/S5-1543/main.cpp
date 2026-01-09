
#include <iostream>
#include <string>

#define MAX_SENTENCE_SIZE (2501U)
#define MAX_WORD_SIZE (51U)

int main()
{
    std::string sentence;
    sentence.reserve(MAX_SENTENCE_SIZE);

    std::getline(std::cin, sentence);

    std::string word;
    word.reserve(MAX_WORD_SIZE);

    std::getline(std::cin, word);

    unsigned int wordFoundCount = 0;
    size_t searchIndex = 0;

    while (true)
    {
        searchIndex = sentence.find(word, searchIndex);
        if (searchIndex == std::string::npos)
        {
            break;
        }

        ++wordFoundCount;

        searchIndex += word.size();
    }

    std::cout << wordFoundCount;

    return 0;
}