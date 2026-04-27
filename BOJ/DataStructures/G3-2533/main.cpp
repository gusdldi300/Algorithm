
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#define MAX_NODES_COUNT (101U)

static std::vector<unsigned int> sConnectedNodeList[MAX_NODES_COUNT];
static unsigned int sEarlyAdapterCounts[MAX_NODES_COUNT][2];

static void SetEarlyAdaptersRecursive(unsigned int node)
{
    sEarlyAdapterCounts[node][0] = 0;
    sEarlyAdapterCounts[node][1] = 1;

    for (unsigned int childNode : sConnectedNodeList[node])
    {
        if (sEarlyAdapterCounts[childNode][0] != UINT_MAX)
        {
            continue;
        }

        SetEarlyAdaptersRecursive(childNode);

        sEarlyAdapterCounts[node][0] += sEarlyAdapterCounts[childNode][1];
        sEarlyAdapterCounts[node][1] += std::min(sEarlyAdapterCounts[childNode][0], sEarlyAdapterCounts[childNode][1]);
    }
}

int main()
{
    unsigned int nodesCount;
    std::cin >> nodesCount;

    for (unsigned int i = 0; i < nodesCount - 1; ++i)
    {
        unsigned int firstNode;
        unsigned int secondNode;

        std::cin >> firstNode >> secondNode;

        sConnectedNodeList[firstNode].push_back(secondNode);
        sConnectedNodeList[secondNode].push_back(firstNode);
    }
    
    memset(sEarlyAdapterCounts, UINT_MAX, sizeof(sEarlyAdapterCounts));
    SetEarlyAdaptersRecursive(1);

    std::cout << std::min(sEarlyAdapterCounts[1][0], sEarlyAdapterCounts[1][1]);

    return 0;
}