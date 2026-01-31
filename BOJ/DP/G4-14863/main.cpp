
#include <iostream>
#include <cstring>

#define MAX_CITIES_COUNT (101U)
#define MAX_TIME (100001U)

int main()
{
    unsigned int citiesCount;
    unsigned int maxTime;
    std::cin >> citiesCount >> maxTime;

    unsigned int maxFunds[MAX_CITIES_COUNT][MAX_TIME] = { 0, };

    unsigned int walkTime;
    unsigned int walkFund;

    unsigned int cycleTime;
    unsigned int cycleFund;

    std::cin >> walkTime >> walkFund >> cycleTime >> cycleFund;

    maxFunds[1][walkTime] = walkFund;
    maxFunds[1][cycleTime] = std::max(maxFunds[1][cycleTime], cycleFund);

    for (unsigned int city = 2; city <= citiesCount; ++city)
    {
        std::cin >> walkTime >> walkFund >> cycleTime >> cycleFund;

        for (unsigned int time = 0; time <= maxTime; ++time)
        {
            if (maxFunds[city - 1][time] <= 0)
            {
                continue;
            }

            unsigned int cityWalkTime = time + walkTime;
            if (cityWalkTime <= maxTime)
            {
                maxFunds[city][cityWalkTime] = std::max(maxFunds[city][cityWalkTime], maxFunds[city - 1][time] + walkFund);
            }

            unsigned int cityCycleTime = time + cycleTime;
            if (cityCycleTime <= maxTime)
            {
                maxFunds[city][cityCycleTime] = std::max(maxFunds[city][cityCycleTime], maxFunds[city - 1][time] + cycleFund);
            }
        }
    }

    unsigned int maxFund = 0;
    for (unsigned int time = 0; time <= maxTime; ++time)
    {
        if (maxFunds[citiesCount][time] > 0)
        {
            maxFund = std::max(maxFund, maxFunds[citiesCount][time]);
        }
    }

    std::cout << maxFund;

    return 0;
}