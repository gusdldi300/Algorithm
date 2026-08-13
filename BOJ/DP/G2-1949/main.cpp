
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#define MAX_VILLAGES_COUNT (10001U)

struct Village
{
    int Habitants;
    std::vector<unsigned int> ChildrenIndexes;
};

static Village sVillages[MAX_VILLAGES_COUNT];

static bool sbVisiteds[2][MAX_VILLAGES_COUNT];
static int sMaxSuperHabitants[2][MAX_VILLAGES_COUNT];

static int GetMaxSuperVillageHabitantsRecursive(bool bSuper, unsigned int parentIndex, unsigned int villagesIndex)
{
    unsigned int superIndex = bSuper ? 1 : 0;
    if (sMaxSuperHabitants[superIndex][villagesIndex] >= 0)
    {
        return sMaxSuperHabitants[superIndex][villagesIndex];
    }

    int maxSuperHabitants = 0;
    if (bSuper)
    {
        for (unsigned int nextVillagesIndex : sVillages[villagesIndex].ChildrenIndexes)
        {
            if (nextVillagesIndex == parentIndex)
            {
                continue;
            }

            maxSuperHabitants += GetMaxSuperVillageHabitantsRecursive(false, villagesIndex, nextVillagesIndex);
        }

        maxSuperHabitants += sVillages[villagesIndex].Habitants;
    }
    else
    {
        for (unsigned int nextVillagesIndex : sVillages[villagesIndex].ChildrenIndexes)
        {
            if (nextVillagesIndex == parentIndex)
            {
                continue;
            }

            int superHabitants = GetMaxSuperVillageHabitantsRecursive(true, villagesIndex, nextVillagesIndex);
            superHabitants = std::max(superHabitants, GetMaxSuperVillageHabitantsRecursive(false, villagesIndex, nextVillagesIndex));

            maxSuperHabitants += superHabitants;
        }
    }

    sMaxSuperHabitants[superIndex][villagesIndex] = maxSuperHabitants;

    return maxSuperHabitants;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int villagesCount;
    std::cin >> villagesCount;
    
    for (unsigned int i = 0; i < villagesCount; ++i)
    {
        std::cin >> sVillages[i].Habitants;
    }

    for (unsigned int i = 0; i < villagesCount - 1; ++i)
    {
        unsigned int villageIndex;
        unsigned int otherVillageIndex;

        std::cin >> villageIndex >> otherVillageIndex;
        --villageIndex;
        --otherVillageIndex;

        sVillages[villageIndex].ChildrenIndexes.push_back(otherVillageIndex);
        sVillages[otherVillageIndex].ChildrenIndexes.push_back(villageIndex);
    }

    memset(sMaxSuperHabitants, -1, sizeof(sMaxSuperHabitants));

    int maxSuperHabitants = GetMaxSuperVillageHabitantsRecursive(true, 0, 0);
    maxSuperHabitants = std::max(maxSuperHabitants, GetMaxSuperVillageHabitantsRecursive(false, 0, 0));

    std::cout << maxSuperHabitants;

    return 0;
}