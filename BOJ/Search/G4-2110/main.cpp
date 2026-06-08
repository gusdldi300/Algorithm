
#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int housesCount;
    unsigned int maxRoutersCount;
    std::cin >> housesCount >> maxRoutersCount;

    std::vector<unsigned int> houses;
    for (unsigned int i = 0; i < housesCount; ++i)
    {
        unsigned int house;
        std::cin >> house;

        houses.push_back(house);
    }

    std::sort(houses.begin(), houses.end());

    unsigned int startDistance = 0;
    unsigned int endDistance = houses[houses.size() - 1] - houses[0];

    unsigned int maxClosestDistance = UINT_MAX;
    while (startDistance <= endDistance)
    {
        unsigned int closestDistance = (endDistance + startDistance) / 2;
        
        unsigned int lastRouter = houses[0];
        unsigned int routersCount = 1;
        
        for (unsigned int i = 1; i < housesCount; ++i)
        {
            unsigned int house = houses[i];
            
            if (house - lastRouter >= closestDistance)
            {
                ++routersCount;

                lastRouter = house;
            }
        }

        if (routersCount >= maxRoutersCount)
        {
            maxClosestDistance = closestDistance;
            
            startDistance = closestDistance + 1;
        }
        else
        {
            endDistance = closestDistance - 1;
        }
    }

    std::cout << maxClosestDistance;

    return 0;
}