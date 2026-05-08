#include <iostream>
#include <vector>

#define MAX_TRAINS_COUNT (3U)
#define MAX_CARRIAGES_COUNT (50001U)

static unsigned int sCarriagesCount;
static unsigned int sCarriagesPerTrain;

std::vector<unsigned int> sTrainPassengers;

unsigned int sMaxPassengers[MAX_TRAINS_COUNT][MAX_CARRIAGES_COUNT] = { 0, };

static unsigned int GetMaxPassengersRecursive(unsigned int trainsIndex, unsigned int passengersIndex)
{
    if (trainsIndex == MAX_TRAINS_COUNT)
    {
        return 0;
    }

    unsigned int maxPassengersCount = sTrainPassengers.size() - ((MAX_TRAINS_COUNT - trainsIndex - 1) * sCarriagesPerTrain);

    unsigned int passengers = 0;
    for (unsigned int i = passengersIndex; i < maxPassengersCount; ++i)
    {
        if (sMaxPassengers[trainsIndex][passengersIndex] > 0)
        {
            passengers = std::max(passengers, sMaxPassengers[trainsIndex][passengersIndex]);

            break;
        }

        passengers = std::max(passengers, GetMaxPassengersRecursive(trainsIndex + 1, i + sCarriagesPerTrain) + sTrainPassengers[i]);
    }

    sMaxPassengers[trainsIndex][passengersIndex] = passengers;

    return passengers;
}

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

    std::cout << GetMaxPassengersRecursive(0, 0);

    return 0;
}