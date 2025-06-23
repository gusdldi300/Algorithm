
#include <iostream>
#include <string>
#include <unordered_set>

static unsigned int sRemoveCount = 0;

bool IsPalindromeRecursive(int removeStartIndex, int currentRemoveCount, std::unordered_set<int>& removedIndexes, const std::string& testString, char* fixedString)
{
    if (currentRemoveCount == 0)
    {
        // Check palindrome
        int stringSize = testString.size();
        char* newString = fixedString;
        for (int i = 0; i < stringSize; ++i)
        {
            if (removedIndexes.find(i) != removedIndexes.end())
            {   
                continue;
            }

            *newString++ = testString[i];
        }

        int leftIndex = 0;
        int rightIndex = testString.size() - sRemoveCount - 1;
        while (leftIndex < rightIndex)
        {
            if (fixedString[leftIndex] != fixedString[rightIndex])
            {
                return false;
            }

            ++leftIndex;
            --rightIndex;
        }

        /*
        while (true)
        {
            while (removedIndexes.find(leftIndex) != removedIndexes.end())
            {
                ++leftIndex;
            }

            while (removedIndexes.find(rightIndex) != removedIndexes.end())
            {
                --rightIndex;            
            }

            if (leftIndex >= rightIndex)
            {
                break;
            }

            if (testString[leftIndex] != testString[rightIndex])
            {
                return false;
            }

            ++leftIndex;
            --rightIndex;
        }
        */

        return true;
    }

    int stringSize = (int)testString.size();
    for (int i = removeStartIndex; i < stringSize; ++i)
    {
        removedIndexes.insert(i);
        if (IsPalindromeRecursive(i + 1, currentRemoveCount - 1, removedIndexes, testString, fixedString))
        {
            return true;
        }
        removedIndexes.erase(i);
    }

    return false;
}

int main()
{
    std::string testString;
    std::cin >> testString;

    const unsigned int MAX_REMOVE_COUNT = 3;
    const unsigned int MAX_STRING_SIZE = 100001;
    
    char fixedString[MAX_STRING_SIZE];
    std::unordered_set<int> removedIndexes;

    bool bPalindrome = false;
    for (sRemoveCount = 0; sRemoveCount <= MAX_REMOVE_COUNT; sRemoveCount++)
    {
        if (IsPalindromeRecursive(0, sRemoveCount, removedIndexes, testString, fixedString))
        {
            std::cout << sRemoveCount;

            return 0;
        }
    }

    std::cout << -1;
    
    return 0;
}
