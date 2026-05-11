#include <algorithm>
#include <iostream>
#include <vector>

#define MAX_TRAINS_COUNT (3U)
#define MAX_CARRIAGES_COUNT (50001U)

static unsigned int sCarriagesCount;
static unsigned int sCarriagesPerTrain;

std::vector<unsigned int> sTrainPassengers;

unsigned int sMaxPassengers[MAX_TRAINS_COUNT + 2][MAX_CARRIAGES_COUNT] = { 0, };

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    std::cin >> sCarriagesCount;

    std::vector<unsigned int> passengers;
    for (unsigned int i = 0; i < sCarriagesCount; ++i)
    {
        unsigned int passenger;
        std::cin >> passenger;

        passengers.push_back(passenger);
    }

    std::cin >> sCarriagesPerTrain;

    unsigned int trainPassengersCount = 0;
    for (unsigned int i = 0; i < sCarriagesPerTrain; ++i)
    {
        trainPassengersCount += passengers[i];
    }

    sTrainPassengers.push_back(trainPassengersCount);

    for (unsigned int i = 0; i < (sCarriagesCount - sCarriagesPerTrain); ++i)
    {
        trainPassengersCount -= passengers[i];
        trainPassengersCount += passengers[i + sCarriagesPerTrain];

        sTrainPassengers.push_back(trainPassengersCount);
    }

    for (unsigned int train = 0; train < MAX_TRAINS_COUNT; ++train)
    {
        for (unsigned int carriage = train * sCarriagesPerTrain; carriage < sTrainPassengers.size() - 1; ++carriage)
        {
            sMaxPassengers[train][carriage + 1] = std::max(sMaxPassengers[train][carriage + 1], sMaxPassengers[train][carriage]);

            unsigned int nextCarriage = carriage + sCarriagesPerTrain;
            if (nextCarriage < sTrainPassengers.size())
            {
                sMaxPassengers[train + 1][nextCarriage] = sMaxPassengers[train][carriage] + sTrainPassengers[carriage];
            }
        }
    }

    unsigned int maxPassengersCount = 0;
    for (unsigned int carriage = 0; carriage < sTrainPassengers.size(); ++carriage)
    {
        if (carriage <= 0)
        {
            continue;
        }

        maxPassengersCount = std::max(maxPassengersCount, sMaxPassengers[MAX_TRAINS_COUNT - 1][carriage] + sTrainPassengers[carriage]);
    }

    std::cout << maxPassengersCount;

    return 0;
}