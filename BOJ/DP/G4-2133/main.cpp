
#include <iostream>

#define MAX_WALL_SIZE_COL (31U)

static unsigned int sCasesCount[MAX_WALL_SIZE_COL] = { 0, };

int main()
{
    unsigned int wallSizeCol;
    std::cin >> wallSizeCol;

    sCasesCount[2] = 3;

    for (unsigned int col = 3; col <= wallSizeCol; ++col)
    {
        if (col % 2 == 1)
        {
            continue;
        }

        sCasesCount[col] = (sCasesCount[2] * sCasesCount[col - 2]) + 2;
        for (unsigned int lastCol = 2; lastCol < (col - 2); lastCol += 2)
        {
            sCasesCount[col] += (2 * sCasesCount[lastCol]);
        }
    }

    std::cout << sCasesCount[wallSizeCol];

    return 0;
}