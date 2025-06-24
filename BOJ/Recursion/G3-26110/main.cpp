
#include <iostream>
#include <string>

#define MAX_REMOVE_COUNT (3)

int GetPalindromeRemoveCountRecursive(int leftStartIndex, int rightStartIndex, int removeCount, const std::string& testString)
{
    if (removeCount > MAX_REMOVE_COUNT)
    {
        return MAX_REMOVE_COUNT + 1;
    }

    int leftIndex = leftStartIndex;
    int rightIndex = rightStartIndex;

    bool bPalindrome = true;
    while (leftIndex < rightIndex)
    {
        if (testString[leftIndex] != testString[rightIndex])
        {
            bPalindrome = false;

            break;
        }

        ++leftIndex;
        --rightIndex;
    }

    if (bPalindrome)
    {
        return removeCount;
    }

    int leftRemovedCount = GetPalindromeRemoveCountRecursive(leftIndex + 1, rightIndex, removeCount + 1, testString);
    int rightRemovedCount = GetPalindromeRemoveCountRecursive(leftIndex, rightIndex - 1, removeCount + 1, testString);

    return leftRemovedCount <= rightRemovedCount ? leftRemovedCount : rightRemovedCount;
}

int main()
{
    std::string testString;
    std::cin >> testString;

    int minRemovedCount = GetPalindromeRemoveCountRecursive(0, testString.size() - 1, 0, testString);
    if (minRemovedCount <= MAX_REMOVE_COUNT)
    {
        std::cout << minRemovedCount;
    }
    else
    {
        std::cout << -1;
    }
    
    return 0;
}
