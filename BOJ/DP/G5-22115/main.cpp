
#include <iostream>

#define MAX_CAFFEIN_AMOUNT (100001U)
#define MAX_COFFEE_COUNT (101U)

static unsigned int sMinCoffeeCounts[MAX_COFFEE_COUNT][MAX_CAFFEIN_AMOUNT];

int main()
{
    unsigned int coffeeCount;
    unsigned int targetCaffeinAmount;

    std::cin >> coffeeCount >> targetCaffeinAmount;

    for (unsigned int i = 0; i <= coffeeCount; ++i)
    {
        for (unsigned int j = 0; j <= targetCaffeinAmount; ++j)
        {
            sMinCoffeeCounts[i][j] = MAX_CAFFEIN_AMOUNT;
        }
    }

    for (unsigned int i = 1; i <= coffeeCount; ++i)
    {
        unsigned int coffeeCaffein;
        std::cin >> coffeeCaffein;

        for (unsigned int checkCaffein = 1; checkCaffein < coffeeCaffein; ++checkCaffein)
        {
            sMinCoffeeCounts[i][checkCaffein] = sMinCoffeeCounts[i - 1][checkCaffein];
        }

        sMinCoffeeCounts[i][coffeeCaffein] = 1;

        for (unsigned int caffein = coffeeCaffein + 1; caffein <= targetCaffeinAmount; ++caffein)
        {
            int lastCaffein = static_cast<int>(caffein) - static_cast<int>(coffeeCaffein);
            if (lastCaffein <= 0)
            {
                continue;
            }

            sMinCoffeeCounts[i][caffein] = std::min(sMinCoffeeCounts[i - 1][caffein], sMinCoffeeCounts[i - 1][lastCaffein] + 1);
        }
    }

    if (targetCaffeinAmount == 0)
    {
        std::cout << 0;

        return 0;
    }
    
    if (sMinCoffeeCounts[coffeeCount][targetCaffeinAmount] == MAX_CAFFEIN_AMOUNT)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << sMinCoffeeCounts[coffeeCount][targetCaffeinAmount];
    }

    return 0;
}