
#include <iostream>
#include <vector>

#define MAX_BUILDINGS_SIZE (8U)
#define MAX_TIME (100001U)
#define CASE_DIVISOR (1000000007U)

static unsigned int sPaths[MAX_TIME][MAX_BUILDINGS_SIZE] = { 0, };
static std::vector<unsigned int> sMap[MAX_BUILDINGS_SIZE];
// 0. Jeongbo
// 1. JeonSan
// 2. Mirae
// 3. Sinyang
// 4. Hankyeong
// 5. Jinri
// 6. Hyeongnam
// 7. HakSaeng

int main()
{
    sMap[0].push_back(1);
    sMap[0].push_back(2);

    sMap[1].push_back(0);
    sMap[1].push_back(2);
    sMap[1].push_back(3);
    
    sMap[2].push_back(0);
    sMap[2].push_back(1);
    sMap[2].push_back(3);
    sMap[2].push_back(4);

    sMap[3].push_back(1);
    sMap[3].push_back(2);
    sMap[3].push_back(4);
    sMap[3].push_back(5);

    sMap[4].push_back(2);
    sMap[4].push_back(3);
    sMap[4].push_back(5);
    sMap[4].push_back(6);

    sMap[5].push_back(3);
    sMap[5].push_back(4);
    sMap[5].push_back(7);

    sMap[6].push_back(4);
    sMap[6].push_back(7);
    
    sMap[7].push_back(5);
    sMap[7].push_back(6);

    unsigned int targetTime = 0;
    std::cin >> targetTime;
    
    sPaths[0][0] = 1;
    for (unsigned int time = 1; time <= targetTime; ++time)
    {
        for (unsigned int building = 0; building < MAX_BUILDINGS_SIZE; ++building)
        {
            unsigned int lastPath = sPaths[time - 1][building];
            if (lastPath == 0)
            {
                continue;
            }

            std::vector<unsigned int>& nextBuildings = sMap[building];
            for (unsigned int nextBuilding : nextBuildings)
            {
                sPaths[time][nextBuilding] = (sPaths[time][nextBuilding] + lastPath) % CASE_DIVISOR;
            }
        }
    }

    std::cout << sPaths[targetTime][0];

    return 0;
}