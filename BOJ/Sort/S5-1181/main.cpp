
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

bool CompareWord(const std::string& first, const std::string& second)
{
    if (first.size() == second.size())
    {
        return first < second;
    }

    return first.size() < second.size();
}

int main()
{
    unsigned int wordsCount;
    std::cin >> wordsCount;

    std::unordered_set<std::string> wordSet;
    for (unsigned int i = 0; i < wordsCount; ++i)
    {
        std::string word; 
        std::cin >> word;

        wordSet.insert(word);
    }

    std::vector<std::string> wordsOrdered;
    for (const std::string& word : wordSet)
    {
        wordsOrdered.push_back(word);
    }

    std::sort(wordsOrdered.begin(), wordsOrdered.end(), CompareWord);
    
    for (const std::string& word : wordsOrdered)
    {
        std::cout << word << std::endl;
    }

    return 0;
}