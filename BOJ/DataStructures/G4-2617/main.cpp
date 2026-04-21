#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#define MAX_BEADS_COUNT (100U)

unsigned int GetBeadsCountRecursive(unsigned int bead, bool bVisited[], std::vector<unsigned int> beadLists[])
{
    unsigned int beadCount = 0;
    for (unsigned int nextBead : beadLists[bead])
    {
        if (bVisited[nextBead])
        {
            continue;
        }

        beadCount += (GetBeadsCountRecursive(nextBead, bVisited, beadLists) + 1);
    }
    
    bVisited[bead] = true;

    return beadCount;
}

int main()
{
    unsigned int beadsCount;
    unsigned int comparisonsCount;
    std::cin >> beadsCount >> comparisonsCount;
    
    std::vector<unsigned int> heavierLists[MAX_BEADS_COUNT];
    std::vector<unsigned int> lighterLists[MAX_BEADS_COUNT];

    for (unsigned int i = 0; i < comparisonsCount; ++i)
    {
        unsigned int heavierBead;
        unsigned int bead;
        
        std::cin >> heavierBead >> bead;
        heavierLists[bead].push_back(heavierBead);
        lighterLists[heavierBead].push_back(bead);
    }

    unsigned int exceptionLighter = (beadsCount / 2) + 1;
    unsigned int exceptionHeavier = exceptionLighter;

    if ((beadsCount % 2) == 0)
    {
        --exceptionLighter;
    }

    bool bVisited[MAX_BEADS_COUNT] = { false, };

    unsigned int exceptionCount = 0;
    for (unsigned int bead = 1; bead <= beadsCount; ++bead)
    {
        unsigned int lighterCount = GetBeadsCountRecursive(bead, bVisited, lighterLists);
        if (lighterCount >= exceptionLighter)
        {
            ++exceptionCount;
        }

        memset(bVisited, 0, sizeof(bVisited));
        unsigned int heavierCount = GetBeadsCountRecursive(bead, bVisited, heavierLists);
        if (heavierCount >= exceptionHeavier)
        {
            ++exceptionCount;
        }

        memset(bVisited, 0, sizeof(bVisited));
    }

    std::cout << exceptionCount;

    return 0;
}