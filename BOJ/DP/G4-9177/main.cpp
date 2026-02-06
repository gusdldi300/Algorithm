
#include <iostream>

#define MAX_WORD_SIZE (201U)

static bool IsStringsMixableRecursive(const std::string& mixedWord, unsigned int mixedIndex, 
                                      const std::string& firstWord, unsigned int firstIndex, 
                                      const std::string& secondWord, unsigned int secondIndex,
                                      bool bNotMixable[MAX_WORD_SIZE][MAX_WORD_SIZE])
{
    if (mixedIndex >= mixedWord.size())
    {
        return true;
    }

    if (bNotMixable[firstIndex][secondIndex])
    {
        return false;
    }

    char mixedChar = mixedWord[mixedIndex];
    if (firstIndex < firstWord.size() && firstWord[firstIndex] == mixedChar)
    {
        if (IsStringsMixableRecursive(mixedWord, mixedIndex + 1, firstWord, firstIndex + 1, secondWord, secondIndex, bNotMixable))
        {
            return true;
        }

        bNotMixable[firstIndex + 1][secondIndex] = true;
    }

    if (secondIndex < secondWord.size() && secondWord[secondIndex] == mixedChar)
    {
        if (IsStringsMixableRecursive(mixedWord, mixedIndex + 1, firstWord, firstIndex, secondWord, secondIndex + 1, bNotMixable))
        {
            return true;
        }
        
        bNotMixable[firstIndex][secondIndex + 1] = true;
    }

    return false;
}

int main()
{
    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int i = 1; i <= testsCount; ++i)
    {
        std::string firstWord;
        std::string secondWord;

        std::string testWord;

        std::cin >> firstWord >> secondWord >> testWord;

        bool bNotMixable[MAX_WORD_SIZE][MAX_WORD_SIZE] = { false, };

        std::cout << "Data set " << i << ": ";
        if (IsStringsMixableRecursive(testWord, 0, firstWord, 0, secondWord, 0, bNotMixable))
        {
            std::cout << "yes";
        }
        else
        {
            std::cout << "no";
        }

        std::cout << '\n';
    }

    return 0;
}