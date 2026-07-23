
#include <cassert>

#include "MergeSort.h"

void MergeSort::SortAscend(std::vector<int>* outNumbers)
{
    assert(outNumbers != nullptr);
    
    if (outNumbers->empty())
    {
        return;
    }

    std::vector<int> tempNumbers(outNumbers->size());
    sortRecursive(*outNumbers, tempNumbers, 0, static_cast<int>(tempNumbers.size() - 1));
}

void MergeSort::sortRecursive(std::vector<int>& outNumbers, std::vector<int>& tempNumbers, int beginIndex, int endIndex)
{
    if (beginIndex >= endIndex)
    {
        return;
    }
    
    int midIndex = (beginIndex + endIndex) / 2;
    sortRecursive(outNumbers, tempNumbers, beginIndex, midIndex);
    sortRecursive(outNumbers, tempNumbers, midIndex + 1, endIndex);

    // Merge sorted numbers and sort
    {
        int leftArrayIndex = beginIndex;
        int rightArrayIndex = midIndex + 1;

        int mergedIndex = beginIndex;

        while (true)
        {
            if (leftArrayIndex > midIndex || rightArrayIndex > endIndex)
            {
                break;
            }

            if (outNumbers[leftArrayIndex] <= outNumbers[rightArrayIndex])
            {
                tempNumbers[mergedIndex] = outNumbers[leftArrayIndex];
                ++leftArrayIndex;
            }
            else
            {
                tempNumbers[mergedIndex] = outNumbers[rightArrayIndex];
                ++rightArrayIndex;
            }

            ++mergedIndex;
        }

        while (leftArrayIndex <= midIndex)
        {
            tempNumbers[mergedIndex] = outNumbers[leftArrayIndex];

            ++mergedIndex;
            ++leftArrayIndex;
        }

        while (rightArrayIndex <= endIndex)
        {
            tempNumbers[mergedIndex] = outNumbers[rightArrayIndex];

            ++mergedIndex;
            ++rightArrayIndex;
        }
    }

    for (int mergedIndex = beginIndex; mergedIndex <= endIndex; ++mergedIndex)
    {
        outNumbers[mergedIndex] = tempNumbers[mergedIndex];
    }
}
