
#include <iostream>

#define MAX_CAGE_SIZE_ROW (3U)
#define MAX_CAGE_SIZE_COL (100001U)

#define LIONS_DIVISOR (9901U)

static unsigned int sLions[MAX_CAGE_SIZE_ROW][MAX_CAGE_SIZE_COL] = { 0, };

int main()
{
    unsigned int cageSizeCol = 0;
    std::cin >> cageSizeCol;

    sLions[0][1] = 1;
    sLions[1][1] = 1;
    sLions[2][1] = 1;

    for (unsigned int cageCol = 2; cageCol <= cageSizeCol; ++cageCol)
    {
        unsigned int lastCol = cageCol - 1;

        sLions[0][cageCol] = (sLions[1][lastCol] + sLions[2][lastCol]) % LIONS_DIVISOR;
        sLions[1][cageCol] = (sLions[0][lastCol] + sLions[2][lastCol]) % LIONS_DIVISOR;
        sLions[2][cageCol] = (sLions[0][lastCol] + sLions[1][lastCol] + sLions[2][lastCol]) % LIONS_DIVISOR;
    }

    std::cout << (sLions[0][cageSizeCol] + sLions[1][cageSizeCol] + sLions[2][cageSizeCol]) % LIONS_DIVISOR;

    return 0;
}