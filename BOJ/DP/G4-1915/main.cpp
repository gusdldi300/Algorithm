#include <iostream>

#define MAX_ARRAY_SIZE (1000U)

static unsigned int sSquareCounts[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0, };

int main()
{
    unsigned int arraySizeRow;
    unsigned int arraySizeCol;

    std::cin >> arraySizeRow >> arraySizeCol;

    unsigned int maxSquareLength = 0;

    for (unsigned int row = 0; row < arraySizeRow; ++row)
    {
        std::string arrayRowString;
        arrayRowString.reserve(arraySizeCol + 1);

        std::cin >> arrayRowString;

        for (unsigned int col = 0; col < arraySizeCol; ++col)
        {
            if (arrayRowString[col] == '1')
            {
                sSquareCounts[row][col] = 1;
                maxSquareLength = 1;
            }
        }
    }

    for (unsigned int row = 1; row < arraySizeRow; ++row)
    {
        for (unsigned int col = 1; col < arraySizeCol; ++col)
        {
            if (sSquareCounts[row][col] == 0)
            {
                continue;
            }

            unsigned int minLastSquareLength = sSquareCounts[row - 1][col];
            minLastSquareLength = std::min(minLastSquareLength, sSquareCounts[row - 1][col - 1]);
            minLastSquareLength = std::min(minLastSquareLength, sSquareCounts[row][col - 1]);

            if (minLastSquareLength == 0)
            {
                continue;
            }

            sSquareCounts[row][col] = minLastSquareLength + 1;
            maxSquareLength = std::max(maxSquareLength, sSquareCounts[row][col]);
        }
    }

    std::cout << (maxSquareLength * maxSquareLength);

    return 0;
}