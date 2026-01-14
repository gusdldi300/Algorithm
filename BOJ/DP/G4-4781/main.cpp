
#include <iostream>

#define MAX_PRICE (10001U)

int main()
{
    while (true)
    {
        unsigned int maxCalories[MAX_PRICE] = { 0, };

        unsigned int candiesCount;
        float targetPriceFloat;
        
        std::cin >> candiesCount >> targetPriceFloat;

        unsigned int targetPrice = static_cast<unsigned int>(targetPriceFloat * 100.f + 0.5f);
        
        if (candiesCount == 0 && targetPrice == 0)
        {
            break;
        }

        for (unsigned int i = 0; i < candiesCount; ++i)
        {
            unsigned int candyCalorie;
            float candyPriceFloat;

            std::cin >> candyCalorie >> candyPriceFloat;
            
            unsigned int candyPrice = static_cast<unsigned int>(candyPriceFloat * 100.f + 0.5f);

            for (unsigned int price = candyPrice; price <= targetPrice; ++price)
            {
                maxCalories[price] = std::max(maxCalories[price], maxCalories[price - candyPrice] + candyCalorie);
            }
        }

        std::cout << maxCalories[targetPrice] << std::endl;
    }

    return 0;
}
