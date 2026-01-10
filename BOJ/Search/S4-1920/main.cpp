
#include <iostream>
#include <vector>
#include <algorithm>

static bool HasNumberRecursive(int leftIndex, int rightIndex, int number, const std::vector<int>& numbers)
{
    if (leftIndex > rightIndex)
    {
        return false;
    }

    int midIndex = (leftIndex + rightIndex) / 2;
    if (numbers[midIndex] == number)
    {
        return true;
    }

    if (number < numbers[midIndex])
    {
        return HasNumberRecursive(leftIndex, midIndex - 1, number, numbers);
    }

    return HasNumberRecursive(midIndex + 1, rightIndex, number, numbers);
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int numbersCount;
    std::cin >> numbersCount;

    std::vector<int> numbers;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        int number;
        std::cin >> number;

        numbers.push_back(number);
    }

    std::sort(numbers.begin(), numbers.end());

    unsigned int checkNumbersCount;
    std::cin >> checkNumbersCount;

    for (unsigned int i = 0; i < checkNumbersCount; ++i)
    {
        int checkNumber;
        std::cin >> checkNumber;

        bool bExists = HasNumberRecursive(0, numbersCount - 1, checkNumber, numbers);
        std::cout << (bExists == true ? 1 : 0) << '\n';
    }

    return 0;
}