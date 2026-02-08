#include <iostream>

#define MAX_COUNTRIES_COUNT (10001U)

int main()
{
    unsigned int countriesCount;
    std::cin >> countriesCount;
    
    int countryNeedFunds[MAX_COUNTRIES_COUNT];
    for (unsigned int i = 0; i < countriesCount; ++i)
    {
        std::cin >> countryNeedFunds[i];
    }

    int maxFund;
    std::cin >> maxFund;

    int startFund = 0;
    int endFund = maxFund;

    int maxNeedFund = 0;
    while (startFund <= endFund)
    {
        int checkFund = (startFund + endFund) / 2;
        
        int needFund = 0;
        int fundSum = 0;
        for (unsigned int i = 0; i < countriesCount; ++i)
        {
            int clippedFund = std::min(checkFund, countryNeedFunds[i]);
            needFund = std::max(needFund, clippedFund);

            fundSum += clippedFund;
        }
        
        if (fundSum <= maxFund)
        {
            maxNeedFund = std::max(maxNeedFund, needFund);

            startFund = checkFund + 1;
        }
        else
        {
            endFund = checkFund - 1;
        }
    }

    std::cout << maxNeedFund;

    return 0;
} 