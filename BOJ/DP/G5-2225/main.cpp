
#include <iostream>

#define MAX_NUMBER (201U)
#define DIVISOR (1000000000U)

static unsigned int sSumResultCases[MAX_NUMBER][MAX_NUMBER] = { 0, };

int main()
{
    unsigned int number;
    unsigned int count;

    std::cin >> number >> count;

    for (unsigned int i = 0; i < MAX_NUMBER; ++i)
    {
        sSumResultCases[1][i] = 1;
        sSumResultCases[i][0] = 1;
    }

    for (unsigned int i = 1; i <= count; ++i)
    {
        for (unsigned int j = 1; j <= number; ++j)
        {
            sSumResultCases[i][j] = (sSumResultCases[i - 1][j] + sSumResultCases[i][j - 1]) % DIVISOR;
        }
    }

    std::cout << sSumResultCases[count][number];

    return 0;
}