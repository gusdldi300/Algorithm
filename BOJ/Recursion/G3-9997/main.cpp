#include <iostream>
#include <string>

#define VISITED_ALL_ALPHABET_MASKS (0x03FFFFFF)

static unsigned int s_total_sentence_count = 0;

void GetTotalSentenceCountRecursive(unsigned int alphabetMasks, unsigned int wordsIndex, const unsigned int* alphabetMasksWords, unsigned int wordsSize)
{
    if (alphabetMasks == VISITED_ALL_ALPHABET_MASKS)
    {
        s_total_sentence_count++;
    }

    if (wordsIndex == wordsSize)
    {
        return;
    }

    for (unsigned int i = wordsIndex; i < wordsSize; ++i)
    {
        GetTotalSentenceCountRecursive(alphabetMasks | alphabetMasksWords[i], i + 1, alphabetMasksWords, wordsSize);
    }
}

int main()
{
    enum { MAX_WORD_COUNT = 25 };

    unsigned int wordsSize = 0;
    unsigned int alphabetMasksWords[MAX_WORD_COUNT];
    
    std::cin >> wordsSize;
    for (unsigned int i = 0; i < wordsSize; ++i)
    {
        std::string word;
        std::cin >> word;

        unsigned int alphabetMasks = 0;
        for (unsigned int alphabetIndex = 0; alphabetIndex < word.size(); ++alphabetIndex)
        {
            unsigned int alphabetMask = 1 << (word[alphabetIndex] - 'a');
            alphabetMasks |= alphabetMask;
        }

        alphabetMasksWords[i] = alphabetMasks;
    }

    for (unsigned int i = 0; i < wordsSize; ++i)
    {
        GetTotalSentenceCountRecursive(alphabetMasksWords[i], i + 1, alphabetMasksWords, wordsSize);
    }

    std::cout << s_total_sentence_count << std::endl;
    
    return 0;
}