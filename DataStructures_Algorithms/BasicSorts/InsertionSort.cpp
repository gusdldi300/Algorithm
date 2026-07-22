
#include "InsertionSort.h"
#include "Common.h"

void InsertionSort::SortDescend(std::vector<int>* outNumbers)
{
    unsigned int numbersSize = outNumbers->size();

    for (unsigned int startIndex = 0; startIndex < numbersSize; ++startIndex)
    {
        for (unsigned int compareIndex = startIndex; compareIndex > 0; --compareIndex)
        {
            if ((*outNumbers)[compareIndex] <= (*outNumbers)[compareIndex - 1])
            {
                break;
            }

            Common::Swap(&((*outNumbers)[compareIndex]), &((*outNumbers)[compareIndex - 1]));
        }
    }
}
