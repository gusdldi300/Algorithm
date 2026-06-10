
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main()
{
    unsigned int numbersCount;
    int targetDifference;

    std::cin >> numbersCount >> targetDifference;

    std::vector<int> numbersAscend;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        int number;
        std::cin >> number;

        numbersAscend.push_back(number);
    }

    std::sort(numbersAscend.begin(), numbersAscend.end());

    int minDifference = INT_MAX;
    unsigned int rightIndex = 0;
    for (unsigned int leftIndex = 0; leftIndex < numbersCount; ++leftIndex)
    {
        while (rightIndex < numbersCount)
        {
            int difference = numbersAscend[rightIndex] - numbersAscend[leftIndex];

            if (difference >= targetDifference)
            {
                minDifference = std::min(minDifference, difference);

                break;
            }

            if (rightIndex >= (numbersCount - 1))
            {
                break;
            }

            ++rightIndex;
        }
    }

    std::cout << minDifference;

    return 0;
}