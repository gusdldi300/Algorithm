
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

#define MAX_WEIGHTS_COUNT (10U)
#define MAX_INTEGER_DIGIT (5U)

static std::vector<unsigned int> sWeigths;
static std::vector<std::pair<unsigned int, unsigned int>> sEquilibriums;

struct IntegerInfo
{
    unsigned int Integer;
    unsigned int Weight;
};

static bool HasUsedWeight(unsigned int usedWeightFlags, unsigned int weight)
{
    if ((usedWeightFlags & (1 << weight)) > 0)
    {
        return true;
    }

    return false;
}

static void SetUsedWeight(unsigned int* outUsedWeightFlags, unsigned int weight)
{
    (*outUsedWeightFlags) |= (1 << weight);
}

static void ResetUsedWeight(unsigned int* outUsedWeightFlags, unsigned int weight)
{
    (*outUsedWeightFlags) &= ~(1 << weight);
}

static bool CompareEquilibriums(std::pair<unsigned int, unsigned int> first, std::pair<unsigned int, unsigned int> second)
{
    if (first.first == second.first)
    {
        return first.second < second.second;
    }

    return first.first < second.first;
}

static void AddEquilibriumsRecursive(unsigned int digit, const IntegerInfo& integerInfo, unsigned int usedWeightFlags, const IntegerInfo& leftIntegerInfo)
{
    if (digit == MAX_INTEGER_DIGIT)
    {
        if (integerInfo.Weight == leftIntegerInfo.Weight)
        {
            sEquilibriums.push_back(std::pair<unsigned int, unsigned int>(leftIntegerInfo.Integer, integerInfo.Integer));
        }

        return;
    }

    unsigned int copiedUsedWeightFlags = usedWeightFlags;

    for (unsigned int weight : sWeigths)
    {
        if (HasUsedWeight(copiedUsedWeightFlags, weight))
        {
            continue;
        }

        if (weight != 0)
        {
            IntegerInfo newInfo;
            newInfo.Integer = integerInfo.Integer + (weight * pow(10, MAX_INTEGER_DIGIT - digit - 1));
            newInfo.Weight = integerInfo.Weight + (weight * (digit + 1));

            if (newInfo.Weight > leftIntegerInfo.Weight)
            {
                continue;
            }

            SetUsedWeight(&copiedUsedWeightFlags, weight);
            AddEquilibriumsRecursive(digit + 1, newInfo, copiedUsedWeightFlags, leftIntegerInfo);
        }
        else
        {
            AddEquilibriumsRecursive(digit + 1, integerInfo, copiedUsedWeightFlags, leftIntegerInfo);
        }

        ResetUsedWeight(&copiedUsedWeightFlags, weight);
    }
}

static void SetEquilibriumsRecursive(unsigned int digit, const IntegerInfo& integerInfo, unsigned int usedWeightFlags)
{
    if (digit == MAX_INTEGER_DIGIT)
    {
        AddEquilibriumsRecursive(0, { 0, 0 }, usedWeightFlags, integerInfo);

        return;
    }

    unsigned int copiedUsedWeightFlags = usedWeightFlags;

    for (unsigned int weight : sWeigths)
    {
        if (HasUsedWeight(copiedUsedWeightFlags, weight))
        {
            continue;
        }

        if (weight != 0)
        {
            SetUsedWeight(&copiedUsedWeightFlags, weight);
        }

        unsigned int power = MAX_INTEGER_DIGIT - digit - 1;

        IntegerInfo newInfo;
        newInfo.Integer = integerInfo.Integer + (weight * pow(10, power));
        newInfo.Weight = integerInfo.Weight + (weight * (power + 1));
        SetEquilibriumsRecursive(digit + 1, newInfo, copiedUsedWeightFlags);

        ResetUsedWeight(&copiedUsedWeightFlags, weight);
    }
}

int main()
{
    unsigned int weightsSetSize;
    std::cin >> weightsSetSize;

    for (unsigned int i = 0; i < weightsSetSize; ++i)
    {
        unsigned int weight;
        std::cin >> weight;

        sWeigths.push_back(weight);
    }

    sWeigths.push_back(0);

    unsigned int equilibriumIndex;
    std::cin >> equilibriumIndex;

    if (equilibriumIndex == 0)
    {
        std::cout << 0;
        
        return 0;
    }

    SetEquilibriumsRecursive(0, { 0, 0 }, 0);
    std::sort(sEquilibriums.begin(), sEquilibriums.end(), CompareEquilibriums);

    if (equilibriumIndex >= sEquilibriums.size())
    {
        equilibriumIndex = sEquilibriums.size() - 1;
    }

    std::string printInteger;
    printInteger.reserve(MAX_INTEGER_DIGIT * 2 + 1);
    
    printInteger.append(std::to_string(sEquilibriums[equilibriumIndex].first));

    unsigned int tempInteger = sEquilibriums[equilibriumIndex].second;
    unsigned int divisor = pow(10, MAX_INTEGER_DIGIT - 1);

    for (unsigned int i = 0; i < MAX_INTEGER_DIGIT; ++i)
    {
        unsigned int printNumber = tempInteger / divisor;
        printInteger.append(std::to_string(printNumber));

        tempInteger -= (printNumber * divisor);
        divisor /= 10;
    }

    std::cout << printInteger;

    return 0;
}
