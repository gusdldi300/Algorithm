
#include <algorithm>
#include <iostream>

#define MAX_SIZE_COL (100000U)
#define MAX_SIZE_ROW (2U)

static unsigned int sStickers[MAX_SIZE_ROW][MAX_SIZE_COL] = { 0, };
static unsigned int sMaxScores[MAX_SIZE_ROW][MAX_SIZE_COL] = { 0, };

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int testCount = 0;
    std::cin >> testCount;

    for (unsigned int test = 0; test < testCount; ++test)
    {
        unsigned int sizeCol = 0; 
        std::cin >> sizeCol;

        for (unsigned int row = 0; row < MAX_SIZE_ROW; ++row)
        {
            for (unsigned int col = 0; col < sizeCol; ++col)
            {
                std::cin >> sStickers[row][col];
            }
        }

        unsigned int maxScore = 0;

        if (sizeCol == 1)
        {
            maxScore = std::max(sStickers[0][0], sStickers[1][0]);

            goto PRINT_LABEL;
        }

        sMaxScores[0][0] = sStickers[0][0];
        sMaxScores[1][0] = sStickers[1][0];

        sMaxScores[0][1] = sMaxScores[1][0] + sStickers[0][1];
        sMaxScores[1][1] = sMaxScores[0][0] + sStickers[1][1];

        for (unsigned int col = 2; col < sizeCol; ++col)
        {
            sMaxScores[0][col] = std::max(sMaxScores[1][col - 1], sMaxScores[1][col - 2]) + sStickers[0][col];
            sMaxScores[1][col] = std::max(sMaxScores[0][col - 1], sMaxScores[0][col - 2]) + sStickers[1][col];
        }

        for (unsigned int row = 0; row < MAX_SIZE_ROW; ++row)
        {
            for (unsigned int col = sizeCol - 2; col < sizeCol; ++col)
            {
                maxScore = std::max(maxScore, sMaxScores[row][col]);
            }
        }

    PRINT_LABEL:
        std::cout << maxScore << "\n";
    }

    return 0;
}