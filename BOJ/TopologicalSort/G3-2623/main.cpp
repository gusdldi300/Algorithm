
#include <cstring>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <queue>

#define MAX_SINGERS_COUNT (1001U)

std::vector<unsigned int> sNextSingerLists[MAX_SINGERS_COUNT];
bool sbVisited[MAX_SINGERS_COUNT] = { false, };

static bool IsSingersCycledRecursive(unsigned int singer, std::unordered_set<unsigned int>& visitedSingerSet)
{
    bool bCycled = true;

    for (unsigned int nextSinger : sNextSingerLists[singer])
    {
        if (visitedSingerSet.find(nextSinger) != visitedSingerSet.end())
        {
            return true;
        }

        if (sbVisited[nextSinger])
        {
            continue;
        }

        visitedSingerSet.insert(nextSinger);
        sbVisited[nextSinger] = true;

        bCycled = IsSingersCycledRecursive(nextSinger, visitedSingerSet);
        if (bCycled)
        {
            return true;
        }

        visitedSingerSet.erase(nextSinger);
    }

    return false;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int totalSingersCount;
    unsigned int pdsCount;
    
    std::cin >> totalSingersCount >> pdsCount;
    
    unsigned int lastSingerCounts[MAX_SINGERS_COUNT] = { 0, };
    for (unsigned int i = 0; i < pdsCount; ++i)
    {
        unsigned int singersCount;
        std::cin >> singersCount;

        unsigned int lastSinger;
        std::cin >> lastSinger;

        for (unsigned int j = 1; j < singersCount; ++j)
        {
            unsigned int singer;
            std::cin >> singer;

            sNextSingerLists[lastSinger].push_back(singer);
            ++lastSingerCounts[singer];

            lastSinger = singer;
        }
    }

    std::queue<unsigned int> singerQueue;

    std::vector<unsigned int> startSingers;
    for (unsigned int singer = 1; singer <= totalSingersCount; ++singer)
    {
        if (lastSingerCounts[singer] == 0)
        {
            startSingers.push_back(singer);
            singerQueue.push(singer);
        }
    }

    for (unsigned int singer = 1; singer <= totalSingersCount; ++singer)
    {
        if (sbVisited[singer])
        {
            continue;
        }

        std::unordered_set<unsigned int> visitedSingerSet;

        visitedSingerSet.insert(singer);
        sbVisited[singer] = true;

        if (IsSingersCycledRecursive(singer, visitedSingerSet))
        {
            std::cout << 0;

            return 0;
        }
    }

    while (singerQueue.empty() == false)
    {
        unsigned int singer = singerQueue.front();
        singerQueue.pop();

        std::cout << singer << '\n';

        for (unsigned int nextSinger : sNextSingerLists[singer])
        {
            --lastSingerCounts[nextSinger];

            if (lastSingerCounts[nextSinger] == 0)
            {
                singerQueue.push(nextSinger);
            }
        }
    }

    return 0;
}