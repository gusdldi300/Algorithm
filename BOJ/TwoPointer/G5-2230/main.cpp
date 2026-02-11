
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
    unsigned int startIndex = 0;
    for (unsigned int endIndex = 0; endIndex < numbersAscend.size(); ++endIndex)
    {
        while (startIndex < numbersAscend.size())
        {
            int difference = numbersAscend[endIndex] - numbersAscend[startIndex];
            if (difference < targetDifference)
            {
                break;
            }

            minDifference = std::min(minDifference, difference);
            ++startIndex;
        }
    }

    std::cout << minDifference;

    return 0;
}