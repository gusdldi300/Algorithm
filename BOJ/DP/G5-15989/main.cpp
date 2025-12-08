
#include <iostream>

#define MAX_NUMBER (10001U)

static unsigned int sCases[MAX_NUMBER][3] = { 0, };
// 0: 1, 2, 3
// 1: 2, 3
// 2: 3

int main()
{
    sCases[1][0] = 1;
    
    sCases[2][0] = 1;
    sCases[2][1] = 1;

    sCases[3][0] = 2;
    sCases[3][2] = 1;

    for (unsigned int number = 4; number < MAX_NUMBER; ++number)
    {
        sCases[number][0] = sCases[number - 1][0] + sCases[number - 1][1] + sCases[number - 1][2];
        sCases[number][1] = sCases[number - 2][1] + sCases[number - 2][2];
        sCases[number][2] = sCases[number - 3][2];
    }

    unsigned int testCount;
    std::cin >> testCount;

    for (unsigned int test = 0; test < testCount; ++test)
    {
        unsigned int targetNumber;
        std::cin >> targetNumber;

        std::cout << sCases[targetNumber][0] + sCases[targetNumber][1] + sCases[targetNumber][2] << std::endl;
    }

    return 0;
}