
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    unsigned int numbersCount;
    std::cin >> numbersCount;

    std::vector<long long> numbersAscend;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        long long number;
        std::cin >> number;

        long long reversedNumber = 0;
        while (true)
        {
            reversedNumber += (number % 10);

            number /= 10;
            if (number == 0)
            {
                break;
            }

            reversedNumber *= 10;
        }

        numbersAscend.push_back(reversedNumber);
    }

    std::sort(numbersAscend.begin(), numbersAscend.end());

    for (long long number : numbersAscend)
    {
        std::cout << number << std::endl;
    }

    return 0;
}