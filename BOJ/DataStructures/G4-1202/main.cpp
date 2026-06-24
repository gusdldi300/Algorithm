
#include <algorithm>
#include <iostream>
#include <queue>

struct Jewel
{
    unsigned int Weight;
    long long Value;
};

static bool OrderJewelsWeightAscend(const Jewel& first, const Jewel& second)
{
    return first.Weight < second.Weight;
}

struct JewelComparator
{
    bool operator()(const Jewel& first, const Jewel& second)
    {
        return first.Value < second.Value;
    }
};

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int jewelsCount;
    unsigned int bagsCount;
    std::cin >> jewelsCount >> bagsCount;

    std::vector<Jewel> jewelsWeightAscend;
    for (unsigned int i = 0; i < jewelsCount; ++i)
    {
        unsigned int weight;
        unsigned int value;
        std::cin >> weight >> value;

        jewelsWeightAscend.push_back({ weight, value});
    }
    
    std::sort(jewelsWeightAscend.begin(), jewelsWeightAscend.end(), OrderJewelsWeightAscend);

    std::vector<unsigned int> bagAffordWeightsAscend;
    for (unsigned int i = 0; i < bagsCount; ++i)
    {
        unsigned int bagAffordWeight;
        std::cin >> bagAffordWeight;

        bagAffordWeightsAscend.push_back(bagAffordWeight);
    }

    std::sort(bagAffordWeightsAscend.begin(), bagAffordWeightsAscend.end());

    std::priority_queue<Jewel, std::vector<Jewel>, JewelComparator> jewelQueueValueDescend;
    long long totalValue = 0;

    unsigned int jewelIndex = 0;
    for (unsigned int bagWeight : bagAffordWeightsAscend)
    {
        for (jewelIndex; jewelIndex < jewelsWeightAscend.size(); ++jewelIndex)
        {
            if (bagWeight < jewelsWeightAscend[jewelIndex].Weight)
            {
                break;
            }

            jewelQueueValueDescend.push(jewelsWeightAscend[jewelIndex]);
        }

        if (jewelQueueValueDescend.empty() == false)
        {
            Jewel maxValueJewel = jewelQueueValueDescend.top();
            jewelQueueValueDescend.pop();

            totalValue += maxValueJewel.Value;
        }
    }
    
    std::cout << totalValue;

    return 0;
}