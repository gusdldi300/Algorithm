
#include <iostream>

#define MAX_NUMBER (1001U)

int main()
{
    unsigned int numbersCount;
    std::cin >> numbersCount;

    unsigned int primeCount = 0;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        unsigned int number;
        std::cin >> number;

        if (number == 1)
        {
            continue;
        }

        bool bPrime = true;
        for (unsigned int divisor = 2; (divisor * divisor) <= number; ++divisor)
        {
            if ((number % divisor) == 0)
            {
                bPrime = false;

                break;
            }
        }

        if (bPrime)
        {
            ++primeCount;
        }
    }

    std::cout << primeCount;

    return 0;
}