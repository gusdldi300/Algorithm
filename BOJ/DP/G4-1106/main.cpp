
#include <iostream>
#include <algorithm>

#define MAX_CUSTOMERS (1001U)
#define MAX_CITIES (21U)

static unsigned int sMinCosts[MAX_CITIES][MAX_CUSTOMERS] = { 0, };

int main()
{
    unsigned int targetCustomers;
    unsigned int citiesCount;

    std::cin >> targetCustomers >> citiesCount;

    unsigned int cost;
    unsigned int gainedCustomers;
    std::cin >> cost >> gainedCustomers;

    unsigned int nextCost = cost;
    unsigned int nextGainedCustomers = gainedCustomers;
    for (unsigned int customer = 1; customer <= targetCustomers; ++customer)
    {
        sMinCosts[0][customer] = nextCost;

        if (customer == nextGainedCustomers)
        {
            nextGainedCustomers += gainedCustomers;
            nextCost += cost;
        }
    }

    for (unsigned int city = 1; city < citiesCount; ++city)
    {
        std::cin >> cost >> gainedCustomers;

        for (unsigned int customer = 1; customer <= gainedCustomers; ++customer)
        {
            sMinCosts[city][customer] = std::min(cost, sMinCosts[city - 1][customer]);
        }

        for (unsigned int customer = gainedCustomers + 1; customer <= targetCustomers; ++customer)
        {
            sMinCosts[city][customer] = std::min(sMinCosts[city][customer - gainedCustomers] + cost, sMinCosts[city - 1][customer]);
        }
    }

    std::cout << sMinCosts[citiesCount - 1][targetCustomers];

    return 0;
}