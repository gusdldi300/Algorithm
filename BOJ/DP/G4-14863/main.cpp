
#include <iostream>
#include <cstring>

struct Fund
{
    unsigned int Amount;
    unsigned int City;
};

#define MAX_CITIES_COUNT (101U)
#define MAX_TIME (3001U)

int main()
{
    unsigned int citiesCount;
    unsigned int maxTime;
    std::cin >> citiesCount >> maxTime;

    Fund lastMaxFunds[MAX_TIME] = { 0, };
    Fund maxFunds[MAX_TIME] = { 0, };

    for (unsigned int city = 1; city <= citiesCount; ++city)
    {
        unsigned int walkTime;
        unsigned int walkFund;

        unsigned int cycleTime;
        unsigned int cycleFund;

        std::cin >> walkTime >> walkFund >> cycleTime >> cycleFund;

        for (unsigned int time = 0; time <= maxTime; ++time)
        {
            if (lastMaxFunds[time].City != (city - 1))
            {
                continue;
            }

            unsigned int cityWalkTime = time + walkTime;
            if (cityWalkTime <= maxTime)
            {
                maxFunds[cityWalkTime].Amount = std::max(maxFunds[cityWalkTime].Amount, lastMaxFunds[time].Amount + walkFund);
                maxFunds[cityWalkTime].City = city;
            }

            unsigned int cityBycleTime = time + cycleTime;
            if (cityBycleTime <= maxTime)
            {
                maxFunds[cityBycleTime].Amount = std::max(maxFunds[cityBycleTime].Amount, lastMaxFunds[time].Amount + cycleFund);
                maxFunds[cityBycleTime].City = city;
            }
        }
        
        memcpy(lastMaxFunds, maxFunds, sizeof(maxFunds));
    }

    unsigned int maxFund = 0;
    for (unsigned int time = 0; time <= maxTime; ++time)
    {
        if (maxFunds[time].City == citiesCount)
        {
            maxFund = std::max(maxFund, maxFunds[time].Amount);
        }
    }

    std::cout << maxFund;

    return 0;
}