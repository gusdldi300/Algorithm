
#include <cstring>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#define MAX_WORKS_COUNT (10001U)

static unsigned int sWorkTimes[MAX_WORKS_COUNT];
static std::vector<unsigned int> sNextWorkLists[MAX_WORKS_COUNT];

static unsigned int sMinWorkTimes[MAX_WORKS_COUNT];

unsigned int GetTotalWorkTimeRecursive(unsigned int work)
{
    if (sMinWorkTimes[work] != UINT_MAX)
    {
        return sMinWorkTimes[work];
    }

    unsigned int totalWorkTime = 0;
    for (unsigned int nextWork : sNextWorkLists[work])
    {
        totalWorkTime = std::max(totalWorkTime, GetTotalWorkTimeRecursive(nextWork));
    }

    sMinWorkTimes[work] = totalWorkTime + sWorkTimes[work];

    return sMinWorkTimes[work];
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int worksCount;
    std::cin >> worksCount;

    for (unsigned int work = 1; work <= worksCount; ++work)
    {
        unsigned int workTime;
        unsigned int lastWorksCount;
        
        std::cin >> workTime >> lastWorksCount;
        sWorkTimes[work] = workTime;

        for (unsigned int i = 0; i < lastWorksCount; ++i)
        {
            unsigned int lastWork;
            std::cin >> lastWork;

            sNextWorkLists[lastWork].push_back(work);
        }
    }

    memset(sMinWorkTimes, UINT_MAX, sizeof(sMinWorkTimes));

    unsigned int minTotalWorkTime = 0;
    for (unsigned int work = 1; work <= worksCount; ++work)
    {
        if (sMinWorkTimes[work] != UINT_MAX)
        {
            continue;
        }

        minTotalWorkTime = std::max(minTotalWorkTime, GetTotalWorkTimeRecursive(work));
    }

    std::cout << minTotalWorkTime;

    return 0;
}