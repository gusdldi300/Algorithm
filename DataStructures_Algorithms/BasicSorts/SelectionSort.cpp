#include "SelectionSort.h"
#include "Common.h"

void SelectionSort::SortAscend(std::vector<int>* outNumbers)
{
    unsigned int numbersSize = outNumbers->size();

    for (unsigned int startIndex = 0; startIndex < numbersSize; ++startIndex)
    {
        unsigned int minIndex = startIndex;
        for (unsigned int searchMinIndex = startIndex; searchMinIndex < numbersSize; ++searchMinIndex)
        {
            if ((*outNumbers)[searchMinIndex] < (*outNumbers)[minIndex])
            {
                minIndex = searchMinIndex;
            }
        }

        Common::Swap(&((*outNumbers)[startIndex]), &((*outNumbers)[minIndex]));
    }
}