
#include <algorithm>
#include <iostream>

#define MAX_BAG_WEIGHT (100001U)
#define MAX_ITEMS_COUNT (101U)

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int maxItemsCount;
    unsigned int maxBagWeight;

    std::cin >> maxItemsCount >> maxBagWeight;

    unsigned int maxValues[MAX_ITEMS_COUNT][MAX_BAG_WEIGHT] = { 0, };

    for (unsigned int itemIndex = 1; itemIndex <= maxItemsCount; ++itemIndex)
    {
        unsigned int itemWeight;
        unsigned int itemValue;

        std::cin >> itemWeight >> itemValue;

        for (unsigned int bagWeight = 1; bagWeight <= maxBagWeight; ++bagWeight)
        {
            maxValues[itemIndex][bagWeight] = maxValues[itemIndex - 1][bagWeight];

            if (bagWeight >= itemWeight)
            {
                maxValues[itemIndex][bagWeight] = 
                    std::max(maxValues[itemIndex][bagWeight], maxValues[itemIndex - 1][bagWeight - itemWeight] + itemValue);
            }
        }
    }

    std::cout << maxValues[maxItemsCount][maxBagWeight];

    return 0;
}