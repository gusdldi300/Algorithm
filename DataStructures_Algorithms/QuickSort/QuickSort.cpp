
#include "QuickSort.h"
#include <cassert>

void QuickSort::SortAscend(std::vector<int>* outNumbers)
{
    assert(outNumbers != nullptr);

    if (outNumbers->empty())
    {
        return;
    }

    sortRecursive(*outNumbers, 0, static_cast<int>(outNumbers->size() - 1));
}

void QuickSort::sortRecursive(std::vector<int>& outNumbers, int beginIndex, int endIndex)
{
    if (beginIndex >= endIndex)
    {
        return;
    }

    int leftIndex = beginIndex;

    // Partition
    {
        for (int i = beginIndex; i < endIndex; ++i)
        {
            // Pivot: End index
            if (outNumbers[i] >= outNumbers[endIndex])
            {
                continue;
            }

            swapNumber(&outNumbers[i], &outNumbers[leftIndex]);

            ++leftIndex;
        }

        swapNumber(&outNumbers[endIndex], &outNumbers[leftIndex]);
    }
    
    sortRecursive(outNumbers, beginIndex, leftIndex - 1);
    sortRecursive(outNumbers, leftIndex + 1, endIndex);
}

void QuickSort::swapNumber(int* pFirstNumber, int* pSecondNumber)
{
    int tempNumber = *pFirstNumber;
    *pFirstNumber = *pSecondNumber;
    *pSecondNumber = tempNumber;
}


