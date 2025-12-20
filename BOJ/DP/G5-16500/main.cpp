
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

int main()
{
    std::string completeString = "";
    std::cin >> completeString;
    
    unsigned int wordsCount;
    std::cin >> wordsCount;

    std::unordered_set<std::string> wordSet;

    for (unsigned int wordsIndex = 0; wordsIndex < wordsCount; ++wordsIndex)
    {
        std::string word;
        std::cin >> word;

        wordSet.insert(word);
    }

    std::vector<int> endIndexes;
    endIndexes.push_back(completeString.size());

    for (int i = (static_cast<int>(completeString.size()) - 1); i >= 0; --i)
    {
        int endIndexesSize = static_cast<int>(endIndexes.size());
        for (int j = 0; j < endIndexesSize; ++j)
        {
            std::string checkWord = completeString.substr(i, (endIndexes[j] - i));

            if (wordSet.find(checkWord) != wordSet.end())
            {
                endIndexes.push_back(i);

                break;
            }
        }
    }

    if (endIndexes[endIndexes.size() - 1] != 0)
    {
        std::cout << 0;
    }
    else
    {
        std::cout << 1;
    }

    return 0;
}