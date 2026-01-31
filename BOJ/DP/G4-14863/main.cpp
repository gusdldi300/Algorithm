
#include <iostream>
#include <cstring>

struct Fund
{
    unsigned int Amount;
    unsigned int City;
};

#define MAX_CITIES_COUNT (101U)
#define MAX_TIME (100001U)

int main()
{
    unsigned int citiesCount;
    unsigned int maxTime;
    std::cin >> citiesCount >> maxTime;

    Fund* pLastMaxFunds = (Fund*)malloc(sizeof(Fund) * (maxTime + 1));
    memset(pLastMaxFunds, 0, sizeof(Fund) * (maxTime + 1));
    
    Fund* pMaxFunds = (Fund*)malloc(sizeof(Fund) * (maxTime + 1));
    memset(pMaxFunds, 0, sizeof(Fund) * (maxTime + 1));

    unsigned int walkTime;
    unsigned int walkFund;

    unsigned int cycleTime;
    unsigned int cycleFund;

    std::cin >> walkTime >> walkFund >> cycleTime >> cycleFund;

    pLastMaxFunds[walkTime].Amount = walkFund;
    pLastMaxFunds[walkTime].City = 1;

    pLastMaxFunds[cycleTime].Amount = std::max(pLastMaxFunds[cycleTime].Amount, cycleFund);
    pLastMaxFunds[cycleTime].City = 1;

    for (unsigned int city = 2; city <= citiesCount; ++city)
    {
        std::cin >> walkTime >> walkFund >> cycleTime >> cycleFund;

        for (unsigned int time = 0; time <= maxTime; ++time)
        {
            if (pLastMaxFunds[time].City < (city - 1))
            {
                continue;
            }

            unsigned int cityWalkTime = time + walkTime;
            if (cityWalkTime <= maxTime)
            {
                pMaxFunds[cityWalkTime].Amount = std::max(pMaxFunds[cityWalkTime].Amount, pLastMaxFunds[time].Amount + walkFund);
                pMaxFunds[cityWalkTime].City = city;
            }

            unsigned int cityCycleTime = time + cycleTime;
            if (cityCycleTime <= maxTime)
            {
                pMaxFunds[cityCycleTime].Amount = std::max(pMaxFunds[cityCycleTime].Amount, pLastMaxFunds[time].Amount + cycleFund);
                pMaxFunds[cityCycleTime].City = city;
            }
        }
        
        Fund* pTemp = pLastMaxFunds;
        pLastMaxFunds = pMaxFunds;
        pMaxFunds = pTemp;
    }

    unsigned int maxFund = 0;
    for (unsigned int time = 0; time <= maxTime; ++time)
    {
        if (pLastMaxFunds[time].City == citiesCount)
        {
            maxFund = std::max(maxFund, pLastMaxFunds[time].Amount);
        }
    }

    free(pLastMaxFunds);
    free(pMaxFunds);

    std::cout << maxFund;

    return 0;
}