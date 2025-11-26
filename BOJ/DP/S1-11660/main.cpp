
#include <iostream>
#include <string>

#define MAX_GRID_SIZE (1025U)

static unsigned int sSums[MAX_GRID_SIZE][MAX_GRID_SIZE] = { 0, };

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int gridSize = 0;
    unsigned int sumCount = 0;

    std::cin >> gridSize >> sumCount;

    for (unsigned int row = 1; row <= gridSize; ++row)
    {
        for (unsigned int col = 1; col <= gridSize; ++col)
        {
            std::cin >> sSums[row][col];
            
            sSums[row][col] += (sSums[row][col - 1] + sSums[row - 1][col] - sSums[row - 1][col - 1]);
        }
    }

    unsigned int startRow = 0;
    unsigned int startCol = 0;
    unsigned int endRow = 0;
    unsigned int endCol = 0;

    unsigned int sum = 0;
    for (unsigned int count = 0; count < sumCount; ++count)
    {
        std::cin >> startRow >> startCol >> endRow >> endCol;
        
        sum = sSums[endRow][endCol] - sSums[startRow - 1][endCol] - sSums[endRow][startCol - 1] + sSums[startRow - 1][startCol - 1];
        std::cout << sum << "\n";
    }

    return 0;
}