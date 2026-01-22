
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    unsigned int numbersCount;
    std::cin >> numbersCount;

    std::vector<int> numbersAscend;
    numbersAscend.reserve(numbersCount);
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        unsigned int number;
        std::cin >> number;

        numbersAscend.push_back(number);
    }

    std::sort(numbersAscend.begin(), numbersAscend.end());

    std::vector<int> sumNumbers;    
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        for (unsigned int j = i; j < numbersCount; ++j)
        {
            sumNumbers.push_back(numbersAscend[i] + numbersAscend[j]);
        }
    }

    int FoundResult = 0;
    for (int resultIndex = numbersCount - 1; resultIndex >= 0; --resultIndex)
    {
        int result = numbersAscend[resultIndex];

        for (unsigned int sumIndex = 0; sumIndex < sumNumbers.size(); ++sumIndex)
        {
            int sumNumber = sumNumbers[sumIndex];
            if (result <= sumNumber)
            {
                continue;
            }

            int thirdNumber = result - sumNumber;
            if (std::binary_search(numbersAscend.begin(), numbersAscend.end(), thirdNumber))
            {
                FoundResult = result;
                goto FOUND_LABEL;
            }
        }
    }

FOUND_LABEL:
    std::cout << FoundResult;

    return 0;
}