
#include <iostream>

#define MAX_BOARD_SIZE (100U)
static unsigned int sBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { 0, };
static long long sPaths[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { 0, };

int main()
{
    unsigned int boardSize = 0;
    std::cin >> boardSize;

    for (unsigned int row = 0; row < boardSize; ++row)
    {
        for (unsigned int col = 0; col < boardSize; ++col)
        {
            std::cin >> sBoard[row][col];
        }
    }

    sPaths[0][0] = 1;
    for (unsigned int row = 0; row < boardSize; ++row)
    {
        for (unsigned int col = 0; col < boardSize; ++col)
        {
            if (sPaths[row][col] == 0)
            {
                continue;
            }

            unsigned int moveCount = sBoard[row][col];
            if (moveCount == 0)
            {
                continue;
            }
            
            unsigned int jumpCol = col + moveCount;
            if (jumpCol < boardSize)
            {
                sPaths[row][jumpCol] += sPaths[row][col];
            }

            unsigned int jumpRow = row + moveCount;
            if (jumpRow < boardSize)
            {
                sPaths[jumpRow][col] += sPaths[row][col];
            }
        }
    }

    std::cout << sPaths[boardSize - 1][boardSize - 1];

    return 0;
}