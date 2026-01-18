
#include <iostream>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int number;
    std::cin >> number;

    unsigned int dividedNumber = number;
    for (unsigned int primeFactor = 2; (primeFactor * primeFactor) <= dividedNumber; ++primeFactor)
    {
        while ((dividedNumber % primeFactor) == 0)
        {
            dividedNumber /= primeFactor;

            std::cout << primeFactor << '\n';
        }
    }

    if (dividedNumber > 1)
    {
        std::cout << dividedNumber;
    }

    return 0;
}