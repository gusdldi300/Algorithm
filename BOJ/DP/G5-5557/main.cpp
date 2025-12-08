
#include <iostream>
#include <cassert>

#define MAX_NUMBER_COUNT (100U)

#define MIN_NUMBER (0)
#define MAX_NUMBER (20)

static long long sOperationCounts[MAX_NUMBER_COUNT][MAX_NUMBER + 1] = {0,};

int main()
{
    int numberCount = 0;
    std::cin >> numberCount;

    assert(numberCount >= 3);

    int number;
    std::cin >> number;
    
    sOperationCounts[0][number] = 1;

    for (int i = 1; i < numberCount - 1; ++i)
    {
        std::cin >> number;

        for (int j = 0; j <= MAX_NUMBER; ++j)
        {
            if ((j + number) <= MAX_NUMBER)
            {
                sOperationCounts[i][j + number] += sOperationCounts[i - 1][j];
            }

            if ((j - number) >= MIN_NUMBER)
            {
                sOperationCounts[i][j - number] += sOperationCounts[i - 1][j];
            }
        }
    }

    std::cin >> number;
    std::cout << sOperationCounts[numberCount - 2][number];

    return 0;
}