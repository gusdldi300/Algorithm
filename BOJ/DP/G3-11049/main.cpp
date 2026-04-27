
#include <iostream>
#include <climits>

#define MAX_MATRICES_COUNT (501U)

struct Matrix
{
    unsigned int RowSize;
    unsigned int ColSize;
};

int main()
{
    unsigned int matricesCount;
    std::cin >> matricesCount;

    unsigned int minMultiplyCounts[MAX_MATRICES_COUNT][MAX_MATRICES_COUNT] = { 0, };
    Matrix matrices[MAX_MATRICES_COUNT];

    for (unsigned int i = 0; i < matricesCount; ++i)
    {
        std::cin >> matrices[i].RowSize >> matrices[i].ColSize;
    }

    for (unsigned int multipliedLength = 2; multipliedLength <= matricesCount; ++multipliedLength)
    {
        for (unsigned int startIndex = 0; startIndex <= (matricesCount - multipliedLength); ++startIndex)
        {
            unsigned int endIndex = startIndex + multipliedLength - 1;
            minMultiplyCounts[startIndex][endIndex] = UINT_MAX;

            for (unsigned int splitIndex = startIndex; splitIndex < endIndex; ++splitIndex)
            {
                unsigned int multiplyCount =
                    minMultiplyCounts[startIndex][splitIndex] + minMultiplyCounts[splitIndex + 1][endIndex] +
                    (matrices[startIndex].RowSize * matrices[splitIndex].ColSize * matrices[endIndex].ColSize);

                minMultiplyCounts[startIndex][endIndex] = std::min(minMultiplyCounts[startIndex][endIndex], multiplyCount);
            }
            
        }
    }
    
    std::cout << minMultiplyCounts[0][matricesCount - 1];

    return 0;
}