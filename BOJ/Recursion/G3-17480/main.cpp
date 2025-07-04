
#include <cstring>
#include <iostream>
#include <unordered_set>

void SeperateWord(const unsigned int startIndex, const unsigned int leftCount, const unsigned int rightCount, const std::string& word, std::unordered_set<std::string>* outNewWords);

void ReverseWord(unsigned int startIndex, unsigned int endIndex, std::string& word)
{
    while (startIndex < endIndex)
    {
        char temp = word[startIndex];
        word[startIndex] = word[endIndex];
        word[endIndex] = temp;

        startIndex++;
        endIndex--;
    }
}

void GetNewWordsRecursive(const unsigned int startIndex, const unsigned int count, const std::string& word, std::unordered_set<std::string>* outNewWords)
{
    if (outNewWords->find(word) != outNewWords->end())
    {
        return;
    }

    if (count <= 1)
    {
        outNewWords->insert(word);

        return;
    }

    unsigned int leftCount = count / 2;
    unsigned int rightCount = leftCount;

    if (count % 2 != 0)
    {
        rightCount++;
        SeperateWord(startIndex, rightCount, leftCount, word, outNewWords);
    }

    SeperateWord(startIndex, leftCount, rightCount, word, outNewWords);
}

void SeperateWord(const unsigned int startIndex, const unsigned int leftCount, const unsigned int rightCount, const std::string& word, std::unordered_set<std::string>* outNewWords)
{
    std::string newWord = word;
    unsigned int leftWordEndIndex = startIndex + leftCount - 1;

    ReverseWord(startIndex, leftWordEndIndex, newWord);
    GetNewWordsRecursive(leftWordEndIndex + 1, rightCount, newWord, outNewWords);

    newWord = word;
    ReverseWord(leftWordEndIndex + 1, leftWordEndIndex + rightCount, newWord);
    GetNewWordsRecursive(startIndex, leftCount, newWord, outNewWords);
}

int main()
{
    enum
    {
        MAX_ALPHABETS_COUNT = 26
    };

    unsigned int alphabetCounts[MAX_ALPHABETS_COUNT + 1] = { 0, };
    unsigned int usedAlphabetCount = 0;

    std::cin >> usedAlphabetCount;

    unsigned int selectedWordLength = 0;
    for (unsigned int i = 0; i < usedAlphabetCount; ++i)
    {
        char alphabet = 0;
        std::cin >> alphabet;
        
        unsigned int alphabetCount = 0;
        std::cin >> alphabetCount; 

        alphabetCounts[static_cast<unsigned int>(alphabet - 'a')] = alphabetCount;
        selectedWordLength += alphabetCount;
    }

    std::string word;
    std::cin >> word;

    // Select words
    std::unordered_set<std::string> selectedWords;

    unsigned int wordLastIndex = word.size() - selectedWordLength;
    unsigned int checkAlphabetCounts[MAX_ALPHABETS_COUNT + 1] = { 0, };

    for (unsigned int startIndex = 0; startIndex <= wordLastIndex; ++startIndex)
    {
        memcpy(checkAlphabetCounts, alphabetCounts, sizeof(checkAlphabetCounts));
        
        bool bWordSelected = true;
        for (unsigned int wordIndex = startIndex; wordIndex < (startIndex + selectedWordLength); ++wordIndex)
        {
            unsigned int alphabetIndex = word[wordIndex] - 'a';
            if (checkAlphabetCounts[alphabetIndex] <= 0)
            {
                bWordSelected = false;
                break;
            }

            checkAlphabetCounts[alphabetIndex]--;
        }

        if (bWordSelected)
        {
            selectedWords.insert(word.substr(startIndex, selectedWordLength));
        }
    }

    std::unordered_set<std::string> newWords;
    for (std::unordered_set<std::string>::iterator iter = selectedWords.begin(); iter != selectedWords.end(); ++iter)
    {
        GetNewWordsRecursive(0, iter->size(), *iter, &newWords);
    }

    std::cout << newWords.size();

    return 0;
}