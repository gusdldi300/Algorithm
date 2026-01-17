
#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int minNumber = 0;
    unsigned int maxNumber = 0;

    std::cin >> minNumber >> maxNumber;

    std::vector<bool> bPrimes(maxNumber + 1, true);
    bPrimes[0] = false;
    bPrimes[1] = false;

    for (unsigned int number = 2; (number * number) <= maxNumber; ++number)
    {
        if (bPrimes[number] == false)
        {
            continue;
        }

        unsigned int multiplier = number;
        while (true)
        {
            unsigned int notPrimeNumber = number * multiplier;
            if (notPrimeNumber > maxNumber)
            {
                break;
            }

            bPrimes[notPrimeNumber] = false;
            
            ++multiplier;
        }
    }

    for (unsigned int number = minNumber; number <= maxNumber; ++number)
    {
        if (bPrimes[number])
        {
            std::cout << number << '\n';
        }
    }

    return 0;
}