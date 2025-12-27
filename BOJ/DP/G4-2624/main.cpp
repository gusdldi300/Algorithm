#include <iostream>

struct Coin
{
    unsigned int Type;
    unsigned int Count;
};

#define MAX_AMOUNT (10001U)
#define MAX_COIN_TYPE_COUNT (101U)

static unsigned int sChangeCases[MAX_COIN_TYPE_COUNT][MAX_AMOUNT] = { 0, };

int main()
{
    unsigned int targetAmount;
    std::cin >> targetAmount;

    unsigned int coinTypes;
    std::cin >> coinTypes;

    for (unsigned int i = 1; i <= coinTypes; ++i)
    {
        Coin coin;
        std::cin >> coin.Type >> coin.Count;

        for (unsigned int j = 1; j < coin.Type; ++j)
        {
            sChangeCases[i][j] = sChangeCases[i - 1][j];
        }

        for (unsigned int j = coin.Type; j <= targetAmount; ++j)
        {
            for (unsigned int k = 1; k <= coin.Count; ++k)
            {
                int lastCoin = static_cast<int>(j) - static_cast<int>(coin.Type * k);
                if (lastCoin == 0)
                {
                    sChangeCases[i][j] += 1;
                }
                else if (lastCoin > 0)
                {
                    sChangeCases[i][j] += sChangeCases[i - 1][lastCoin];
                }
            }

            sChangeCases[i][j] += sChangeCases[i - 1][j];
        }
    }

    std::cout << sChangeCases[coinTypes][targetAmount];

    return 0;
}