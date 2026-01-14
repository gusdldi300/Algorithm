
#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

class CountingSort
{
public:
    static void SortAscend(const std::vector<int>& numbers, std::vector<int>* outAscendedNumbers);
};

void CountingSort::SortAscend(const std::vector<int>& numbers, std::vector<int>* outAscendedNumbers)
{
    std::unordered_map<int, unsigned int> numberCounts;
    
    int minNumber = INT_MAX;
    int maxNumber = 0;
    for (unsigned int i = 0; i < numbers.size(); ++i)
    {
        int addNumber = numbers[i];
        minNumber = std::min(minNumber, addNumber);
        maxNumber = std::max(maxNumber, addNumber);

        if (numberCounts.find(addNumber) == numberCounts.end())
        {
            numberCounts.insert(std::pair<int, unsigned int>(addNumber, 1));

            continue;
        }

        numberCounts[addNumber] = (numberCounts[addNumber] + 1);
    }

    for (int number = minNumber; number <= maxNumber; ++number)
    {
        if (numberCounts.find(number) == numberCounts.end())
        {
            continue;
        }

        unsigned int numberCount = numberCounts[number];
        for (unsigned int i = 0; i < numberCount; ++i)
        {
            outAscendedNumbers->push_back(number);
        }
    }
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int numbersCount;
    std::cin >> numbersCount;

    std::vector<int> numbers;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        int number;

        std::cin >> number;
        numbers.push_back(number);
    }

    std::vector<int> numbersAscended;
    CountingSort::SortAscend(numbers, &numbersAscended);

    for (int number : numbersAscended)
    {
        std::cout << number << '\n';
    }

    return 0;
}