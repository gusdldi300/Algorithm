
#include <iostream>
#include <unordered_map>

static std::unordered_map<unsigned long long, unsigned long long> InfiniteSequenceValues;

static unsigned long long GetInfiniteSequenceRecursive(unsigned long long index, const unsigned long long firstDivisor, const unsigned long long secondDivisor)
{
    if (index == 0)
    {
        return 1ULL;
    }

    if (InfiniteSequenceValues.find(index) != InfiniteSequenceValues.end())
    {
        return InfiniteSequenceValues.find(index)->second;
    }

    unsigned long long result = GetInfiniteSequenceRecursive(index / firstDivisor, firstDivisor, secondDivisor) +
        GetInfiniteSequenceRecursive(index / secondDivisor, firstDivisor, secondDivisor);

    InfiniteSequenceValues.insert(std::pair<unsigned long long, unsigned long long>(index, result));

    return result;
}

int main()
{
    unsigned long long targetIndex;
    unsigned long long firstDivisor;
    unsigned long long secondDivisor;

    std::cin >> targetIndex >> firstDivisor >> secondDivisor;

    std::cout << GetInfiniteSequenceRecursive(targetIndex, firstDivisor, secondDivisor);

    return 0;
}