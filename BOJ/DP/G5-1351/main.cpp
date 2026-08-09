
#include <iostream>
#include <unordered_map>

static unsigned long long sFirstDivisor;
static unsigned long long sSecondDivisor;

static std::unordered_map<unsigned long long, unsigned long long> sInfiniteSequenceValues;

static unsigned long long GetInfiniteSequenceRecursive(unsigned long long index)
{
    if (index == 0)
    {
        return 1ULL;
    }

    if (sInfiniteSequenceValues.find(index) != sInfiniteSequenceValues.end())
    {
        return sInfiniteSequenceValues.find(index)->second;
    }

    unsigned long long result = 
        GetInfiniteSequenceRecursive(index / sFirstDivisor) +
        GetInfiniteSequenceRecursive(index / sSecondDivisor);

    sInfiniteSequenceValues.insert(std::pair<unsigned long long, unsigned long long>(index, result));

    return result;
}

int main()
{
    unsigned long long targetIndex;
    std::cin >> targetIndex >> sFirstDivisor >> sSecondDivisor;

    std::cout << GetInfiniteSequenceRecursive(targetIndex);

    return 0;
}