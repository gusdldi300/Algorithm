
#include <iostream>
#include <queue>
#include <cassert>

#define MAX_ENERGY (61)
#define MAX_SCV_COUNT (3U)

#define MAX_ATTACK_SEQUEUNCES_COUNT (6U)

#define FIRST_ATTACK_DAMAGE (9)
#define SECOND_ATTACK_DAMAGE (3)
#define THIRD_ATTACK_DAMAGE (1)

static const unsigned int ATTACK_SEQUENCES[MAX_ATTACK_SEQUEUNCES_COUNT][MAX_SCV_COUNT] =
{
    { 0, 1, 2 },
    { 0, 2, 1 },
    { 1, 0, 2 },
    { 1, 2, 0 },
    { 2, 0, 1 },
    { 2, 1, 0 }
};

int main()
{
    std::vector<int> firstScvEnergies;
    firstScvEnergies.reserve(MAX_SCV_COUNT);
    
    unsigned int scvCount;
    std::cin >> scvCount;

    for (unsigned int i = 0; i < scvCount; ++i)
    {
        int scvEnergy;
        std::cin >> scvEnergy;

        firstScvEnergies.push_back(scvEnergy);
    }

    while (firstScvEnergies.size() < MAX_SCV_COUNT)
    {
        firstScvEnergies.push_back(0);
    }

    bool visited[MAX_ENERGY][MAX_ENERGY][MAX_ENERGY] = { false, };

    std::queue<std::vector<int>> scvsQueue;
    scvsQueue.push(firstScvEnergies);
    visited[firstScvEnergies[0]][firstScvEnergies[1]][firstScvEnergies[2]];

    unsigned int attackCount = 0;
    
    while (scvsQueue.empty() == false)
    {
        unsigned int scvsQueueSize = scvsQueue.size();
        for (unsigned int i = 0; i < scvsQueueSize; ++i)
        {
            std::vector<int> scvEnergies = scvsQueue.front();
            scvsQueue.pop();

            if (scvEnergies[0] == 0 && scvEnergies[1] == 0 && scvEnergies[2] == 0)
            {
                goto ATTACK_COMPLETE_LABEL;
            }

            for (unsigned int j = 0; j < MAX_ATTACK_SEQUEUNCES_COUNT; ++j)
            {
                std::vector<int> nextScvEnergies;
                nextScvEnergies.reserve(MAX_SCV_COUNT);

                for (unsigned int k = 0; k < MAX_SCV_COUNT; ++k)
                {
                    int scvEnergy = scvEnergies[k];

                    switch (ATTACK_SEQUENCES[j][k])
                    {
                    case 0:
                        scvEnergy -= FIRST_ATTACK_DAMAGE;

                        break;
                    case 1:
                        scvEnergy -= SECOND_ATTACK_DAMAGE;

                        break;
                    case 2:
                        scvEnergy -= THIRD_ATTACK_DAMAGE;

                        break;
                    default:
                        assert(false);
                    }

                    scvEnergy = (scvEnergy < 0) ? 0 : scvEnergy;

                    nextScvEnergies.push_back(scvEnergy);
                }

                if (visited[nextScvEnergies[0]][nextScvEnergies[1]][nextScvEnergies[2]])
                {
                    continue;
                }

                visited[nextScvEnergies[0]][nextScvEnergies[1]][nextScvEnergies[2]] = true;
                scvsQueue.push(nextScvEnergies);
            }
        }

        ++attackCount;
    }
    
ATTACK_COMPLETE_LABEL:
    std::cout << attackCount;

    return 0;
}