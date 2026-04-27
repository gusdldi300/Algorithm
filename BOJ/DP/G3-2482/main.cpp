#include <cstring>
#include <iostream>

#define MAX_COLORS_COUNT (1001U)
#define MAX_SELECT_COUNT (1001U)
#define DIVISOR (1000000003)

int sCasesCounts[MAX_COLORS_COUNT][MAX_SELECT_COUNT];

unsigned int sColorsCount;
unsigned int sSelectedCount;

static int GetSelectedCasesRecursive(unsigned int colorsIndex, unsigned int maxColorsCount, unsigned int selectedCount)
{
    if (colorsIndex >= maxColorsCount)
    {
        return 0;
    }

    if (sCasesCounts[colorsIndex][selectedCount] >= 0)
    {
        return sCasesCounts[colorsIndex][selectedCount];
    }

    unsigned int updatedCount = selectedCount;
    
    int casesCount = 0;
    casesCount += GetSelectedCasesRecursive(colorsIndex + 1, maxColorsCount, updatedCount);
    casesCount %= DIVISOR;

    ++updatedCount;
    if (updatedCount == sSelectedCount)
    {
        ++casesCount;

        updatedCount = 0;
    }

    casesCount += GetSelectedCasesRecursive(colorsIndex + 2, maxColorsCount, updatedCount);
    casesCount %= DIVISOR;

    sCasesCounts[colorsIndex][selectedCount] = casesCount;

    return casesCount;
}

int main()
{
    std::cin >> sColorsCount >> sSelectedCount;
    
    memset(sCasesCounts, -1, sizeof(sCasesCounts));
    int casesCount = GetSelectedCasesRecursive(2, sColorsCount - 1, 1);

    memset(sCasesCounts, -1, sizeof(sCasesCounts));
    casesCount += GetSelectedCasesRecursive(1, sColorsCount, 0);
    casesCount %= DIVISOR;

    std::cout << casesCount;

    return 0;
}