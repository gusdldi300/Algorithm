#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int countriesCount;
    std::cin >> countriesCount;
    
    std::vector<int> countriesNeedFunds;
    int endFund = 0;

    for (unsigned int i = 0; i < countriesCount; ++i)
    {
        int fund;
        std::cin >> fund;

        countriesNeedFunds.push_back(fund);

        endFund = std::max(endFund, fund);
    }

    int maxTotalFund;
    std::cin >> maxTotalFund;

    int startFund = 0;

    int maxFund = 0;
    while (startFund <= endFund)
    {
        int candidateMaxFund = (startFund + endFund) / 2;

        int totalFund = 0;
        for (int fund : countriesNeedFunds)
        {
            if (fund >= candidateMaxFund)
            {
                totalFund += candidateMaxFund;

                continue;
            }

            totalFund += fund;
        }

        if (totalFund <= maxTotalFund)
        {
            maxFund = candidateMaxFund;

            startFund = candidateMaxFund + 1;
        }
        else
        {
            endFund = candidateMaxFund - 1;
        }
    }

    std::cout << maxFund;

    return 0;
} 