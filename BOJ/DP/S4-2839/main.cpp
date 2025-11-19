
#include <cassert>
#include <climits>
#include <iostream>

#define MAX_SUGAR_WEIGHT (5000U)
#define MIN_SUGAR_WEIGHT (3U)

int main()
{
    unsigned int targetSugarWeight = 0;
    std::cin >> targetSugarWeight;
    assert(targetSugarWeight >= MIN_SUGAR_WEIGHT && targetSugarWeight <= MAX_SUGAR_WEIGHT);

    unsigned int sugarMinCounts[MAX_SUGAR_WEIGHT + 1] = { 0, };
    sugarMinCounts[1] = UINT_MAX;
    sugarMinCounts[2] = UINT_MAX;
    sugarMinCounts[3] = 1;
    sugarMinCounts[4] = UINT_MAX;
    sugarMinCounts[5] = 1;


    for (unsigned int sugarWeight = 6; sugarWeight <= targetSugarWeight; ++sugarWeight)
    {
        unsigned int first = sugarMinCounts[sugarWeight - 3];
        unsigned int second = sugarMinCounts[sugarWeight - 5];

        if (first == UINT_MAX && second == UINT_MAX)
        {
            sugarMinCounts[sugarWeight] = UINT_MAX;

            continue;
        }

        sugarMinCounts[sugarWeight] = (first < second ? first : second) + 1;
    }

    if (sugarMinCounts[targetSugarWeight] == UINT_MAX)
    {
        std::cout << "-1";
    }
    else
    {
        std::cout << sugarMinCounts[targetSugarWeight];
    }
    
    return 0;
}