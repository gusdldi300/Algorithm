#include <cstring>
#include <iostream>

#define MAX_COLORS_COUNT (1001U)
#define MAX_SELECT_COUNT (1001U)
#define DIVISOR (1000000003)

int sCasesCounts[MAX_COLORS_COUNT][MAX_SELECT_COUNT];

static int GetSelectedCasesRecursive(int colorsCount, int selectCount)
{
    if (colorsCount < ((2 * selectCount) - 1))
    {
        return 0;
    }

    if (selectCount == 1)
    {
        return colorsCount;
    }

    if (sCasesCounts[colorsCount][selectCount] != -1)
    {
        return sCasesCounts[colorsCount][selectCount];
    }

    int casesCount = GetSelectedCasesRecursive(colorsCount - 2, selectCount - 1);
    casesCount += GetSelectedCasesRecursive(colorsCount - 1, selectCount);
    casesCount %= DIVISOR;

    sCasesCounts[colorsCount][selectCount] = casesCount;

    return casesCount;
}

int main()
{
    unsigned int colorsCount;
    unsigned int selectedCount;

    std::cin >> colorsCount >> selectedCount;
    
    memset(sCasesCounts, -1, sizeof(sCasesCounts));
    for (int colorsIndex = 0; colorsIndex < colorsCount; ++colorsIndex)
    {
        sCasesCounts[colorsIndex][0] = 1;
    }
    
    // Select first number
    int casesCount = GetSelectedCasesRecursive(colorsCount - 3, selectedCount - 1);
    
    // Don't select first number
    casesCount += GetSelectedCasesRecursive(colorsCount - 1, selectedCount);

    casesCount %= DIVISOR;

    std::cout << casesCount;

    return 0;
}