
#include <iostream>

#define MAX_NUMBER (1000001U)
#define CASE_DIVISOR (1000000000U)

static unsigned long long sCases[MAX_NUMBER] = { 0, };

int main()
{
    int targetNumber;
    std::cin >> targetNumber;

    sCases[1] = 1;
    for (int number = 2; number <= targetNumber; ++number)
    {
        sCases[number] = sCases[number - 1];

        if (number % 2 == 0)
        {
            sCases[number] = (sCases[number] + sCases[number / 2]) % CASE_DIVISOR;
        }
    }

    std::cout << sCases[targetNumber];

    return 0;
}