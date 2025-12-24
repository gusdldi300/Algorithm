
#include <iostream>
#include <vector>

#define MAX_AMOUNT (10001U)

int main()
{
    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int test = 0; test < testsCount; ++test)
    {
        unsigned int coinsCount;
        std::cin >> coinsCount;
        
        unsigned int minUsedCoins[MAX_AMOUNT] = { 0, };
        std::vector<unsigned int> coins;
        coins.reserve(coinsCount);

        for (unsigned int i = 0; i < coinsCount; ++i)
        {
            unsigned int coin;
            std::cin >> coin;

            coins.push_back(coin);
        }

        unsigned int targetAmount;
        std::cin >> targetAmount;

        minUsedCoins[0] = 1;

        for (unsigned int coin : coins)
        {
            for (unsigned int amount = 1; amount <= targetAmount; ++amount)
            {
                if (amount >= coin)
                {
                    minUsedCoins[amount] = minUsedCoins[amount] + minUsedCoins[amount - coin];
                }
            }

            continue;
        }

        std::cout << minUsedCoins[targetAmount] << std::endl;
    }


    return 0;
}