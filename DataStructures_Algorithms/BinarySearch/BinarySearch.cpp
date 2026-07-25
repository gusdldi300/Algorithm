#include "BinarySearch.h"
#include <cassert>

int BinarySearch::GetNumberFirstIndex(int searchNumber, const std::vector<int>& numbersAscend)
{
    if (numbersAscend.empty())
    {
        return -1;
    }

    int foundIndex = -1;
    searchNumberFirstIndexRecursive(&foundIndex, 0, numbersAscend.size() - 1, searchNumber, numbersAscend);

    return foundIndex;
}

int BinarySearch::GetNumberLastIndex(int searchNumber, const std::vector<int>& numbersAscend)
{
    if (numbersAscend.empty())
    {
        return -1;
    }

    int foundIndex = -1;
    searchNumberLastIndexRecursive(&foundIndex, 0, numbersAscend.size() - 1, searchNumber, numbersAscend);

    return foundIndex;
}

void BinarySearch::searchNumberFirstIndexRecursive(int* outIndex, int leftIndex, int rightIndex, int searchNumber, const std::vector<int>& numbersAscend)
{
    assert(outIndex != nullptr);

    if (leftIndex > rightIndex)
    {
        return;
    }

    int midIndex = (rightIndex + leftIndex) / 2;
    if (searchNumber <= numbersAscend[midIndex])
    {
        if (numbersAscend[midIndex] == searchNumber)
        {
            *outIndex = midIndex;
        }

        searchNumberFirstIndexRecursive(outIndex, leftIndex, midIndex - 1, searchNumber, numbersAscend);
    }
    else
    {
        searchNumberFirstIndexRecursive(outIndex, midIndex + 1, rightIndex, searchNumber, numbersAscend);
    }
}

void BinarySearch::searchNumberLastIndexRecursive(int* outIndex, int leftIndex, int rightIndex, int searchNumber, const std::vector<int>& numbersAscend)
{
    assert(outIndex != nullptr);

    if (leftIndex > rightIndex)
    {
        return;
    }

    int midIndex = (rightIndex + leftIndex) / 2;
    if (searchNumber < numbersAscend[midIndex])
    {
        searchNumberLastIndexRecursive(outIndex, leftIndex, midIndex - 1, searchNumber, numbersAscend);
    }
    else
    {
        if (numbersAscend[midIndex] == searchNumber)
        {
            *outIndex = midIndex;
        }

        searchNumberLastIndexRecursive(outIndex, midIndex + 1, rightIndex, searchNumber, numbersAscend);
    }
}

