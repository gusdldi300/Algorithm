#include <iostream>
#include <string>

#define VISITED_ALL_ALPHABET_MASKS (0x03FFFFFF)

static unsigned int sTotalSentenceCount = 0;

void GetTotalSentenceCountRecursive(unsigned int alphabetMasks, unsigned int wordsIndex, const unsigned int* alphabetMaskedWords, const unsigned int wordsSize)
{
    if (wordsIndex >= wordsSize)
    {
        if (alphabetMasks == VISITED_ALL_ALPHABET_MASKS)
        {
            sTotalSentenceCount++;
        }

        return;
    }

    GetTotalSentenceCountRecursive(alphabetMasks | alphabetMaskedWords[wordsIndex], wordsIndex + 1, alphabetMaskedWords, wordsSize);
    GetTotalSentenceCountRecursive(alphabetMasks, wordsIndex + 1, alphabetMaskedWords, wordsSize);
}

int main()
{
    enum { MAX_WORD_COUNT = 25 };

    unsigned int wordsSize = 0;
    unsigned int alphabetMaskedWords[MAX_WORD_COUNT];
    
    std::cin >> wordsSize;
    for (unsigned int i = 0; i < wordsSize; ++i)
    {
        std::string word;
        std::cin >> word;

        unsigned int alphabetMasks = 0;
        unsigned int wordSize = word.size();
        for (unsigned int alphabetIndex = 0; alphabetIndex < wordSize; ++alphabetIndex)
        {
            alphabetMasks |= (1 << (word[alphabetIndex] - 'a'));
        }

        alphabetMaskedWords[i] = alphabetMasks;
    }

    GetTotalSentenceCountRecursive(0, 0, alphabetMaskedWords, wordsSize);

    std::cout << sTotalSentenceCount;
    
    return 0;
}