#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int numbersCount;
    std::cin >> numbersCount;

    std::vector<unsigned int> ascendNumbers;

    unsigned int number;
    std::cin >> number;
    ascendNumbers.push_back(number);

    for (unsigned int i = 1; i < numbersCount; ++i)
    {
        std::cin >> number;

        if (number > ascendNumbers.back())
        {
            ascendNumbers.push_back(number);

            continue;
        }

        unsigned int equalLessIndex = static_cast<unsigned int>(std::lower_bound(ascendNumbers.begin(), ascendNumbers.end(), number) - ascendNumbers.begin());
        ascendNumbers[equalLessIndex] = number;
    }

    std::cout << ascendNumbers.size();

    return 0;
}