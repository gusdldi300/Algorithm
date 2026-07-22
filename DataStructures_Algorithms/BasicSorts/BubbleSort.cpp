
#include "BubbleSort.h"
#include "Common.h"

void BubbleSort::SortAscend(std::vector<int>* outNumbers)
{
    unsigned int numbersSize = outNumbers->size();

    for (unsigned int count = 0; count < numbersSize; ++count)
    {
        for (unsigned int i = 0; i < numbersSize - count - 1; ++i)
        {
            if ((*outNumbers)[i] <= (*outNumbers)[i + 1])
            {
                continue;
            }

            Common::Swap(&(*outNumbers)[i], &(*outNumbers)[i + 1]);
        }
    }
}
