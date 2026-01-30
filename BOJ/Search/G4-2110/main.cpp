#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    unsigned int housesCount;
    unsigned int targetCount;
    
    std::cin >> housesCount >> targetCount;

    std::vector<int> houseLocations;
    for (unsigned int i = 0; i < housesCount; ++i)
    {
        int location;
        std::cin >> location;

        houseLocations.push_back(location);
    }

    std::sort(houseLocations.begin(), houseLocations.end());

    int startDistance = 0;
    int endDistance = houseLocations[houseLocations.size() - 1];

    int maxDistance = 0;
    while (startDistance <= endDistance)
    {
        int checkDistance = (startDistance + endDistance) / 2;

        unsigned int setCount = 1;
        int setLocation = houseLocations[0] + checkDistance;
        for (unsigned int i = 1; i < houseLocations.size(); ++i)
        {
            if (houseLocations[i] >= setLocation)
            {
                setLocation = houseLocations[i] + checkDistance;
                
                ++setCount;
            }
        }

        if (setCount >= targetCount)
        {
            maxDistance = checkDistance;
            
            startDistance = checkDistance + 1;
        }
        else
        {
            endDistance = checkDistance - 1;
        }
    }
    
    std::cout << maxDistance;

    return 0;
}