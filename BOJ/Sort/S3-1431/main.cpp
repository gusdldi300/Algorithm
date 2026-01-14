
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_GUITARS_COUNT (51U)

unsigned int GetCharNumberSumOf(const std::string& string)
{
    unsigned int sum = 0;
    for (unsigned int i = 0; i < string.size(); ++i)
    {
        if (string[i] >= '0' && string[i] <= '9')
        {
            sum += (string[i] - '0');
        }
    }

    return sum;
}

bool CompareGuitars(const std::string& first, const std::string& second)
{
    if (first.size() == second.size())
    {
        unsigned int firstSum = GetCharNumberSumOf(first);
        unsigned int secondSum = GetCharNumberSumOf(second);

        if (firstSum == secondSum)
        {
            return first < second;
        }

        return firstSum < secondSum;
    }

    return first.size() < second.size();
}

int main()
{
    unsigned int guitarsCount;
    std::cin >> guitarsCount;

    std::string guitarsAscend[MAX_GUITARS_COUNT];

    for (unsigned int i = 0; i < guitarsCount; ++i)
    {
        std::cin >> guitarsAscend[i];
    }

    std::sort(guitarsAscend, guitarsAscend + guitarsCount, CompareGuitars);

    for (unsigned int i = 0; i < guitarsCount; ++i)
    {
        std::cout << guitarsAscend[i] << std::endl;
    }

    return 0;
}