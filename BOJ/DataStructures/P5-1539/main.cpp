#include <iostream>
#include <map>

int main()
{
    unsigned int numbersCount;
    std::cin >> numbersCount;
    
    unsigned int number;
    std::cin >> number;

    std::map<unsigned int, unsigned long long> numberAndHeightMapAscend;
    numberAndHeightMapAscend.insert(std::pair<unsigned int, unsigned int>(number, 1));

    for (unsigned int i = 0; i < numbersCount - 1; ++i)
    {
        std::cin >> number;
        numberAndHeightMapAscend.insert(std::pair<unsigned int, unsigned int>(number, 0));

        unsigned long long parentHeight = 0;
        auto foundIter = numberAndHeightMapAscend.find(number);

        if (foundIter == numberAndHeightMapAscend.begin())
        {
            parentHeight = std::next(foundIter)->second;
        }
        else if (std::next(foundIter) == numberAndHeightMapAscend.end())
        {
            parentHeight = std::prev(foundIter)->second;
        }
        else
        {
            parentHeight = std::max(std::prev(foundIter)->second, std::next(foundIter)->second);
        }

        numberAndHeightMapAscend[number] = parentHeight + 1;
    }

    unsigned long long heightSum = 0;
    for (auto numberAndHeightPair : numberAndHeightMapAscend)
    {
        heightSum += numberAndHeightPair.second;
    }

    std::cout << heightSum;

    return 0;
}