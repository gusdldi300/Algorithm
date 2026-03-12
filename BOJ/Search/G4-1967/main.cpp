
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_NODES_COUNT (10001U)

struct Edge
{
    unsigned int ChildId;
    unsigned int Weight;
};

static std::vector<Edge> sEdgeLists[MAX_NODES_COUNT];
static unsigned int sMaxLength = 0;

// Returns max weight
static unsigned int GetMaxLengthRecursive(unsigned int parentId)
{
    std::vector<unsigned int> weightsAscend;
    for (const Edge& edge : sEdgeLists[parentId])
    {
        unsigned int weight = edge.Weight;
        weight += GetMaxLengthRecursive(edge.ChildId);

        weightsAscend.push_back(weight);
    }

    if (weightsAscend.size() <= 0)
    {
        return 0;
    }

    std::sort(weightsAscend.begin(), weightsAscend.end(), std::greater<unsigned int>());

    unsigned int maxWeight = weightsAscend[0];
    if (weightsAscend.size() <= 1)
    {
        sMaxLength = std::max(sMaxLength, maxWeight);
    }
    else
    {
        sMaxLength = std::max(sMaxLength, maxWeight + weightsAscend[1]);
    }

    return maxWeight;
}

int main()
{
    unsigned int nodesCount;
    std::cin >> nodesCount;

    for (unsigned int i = 0; i < nodesCount - 1; ++i)
    {
        unsigned int parentId;
        unsigned int childId;
        unsigned int weight;

        std::cin >> parentId >> childId >> weight;
        sEdgeLists[parentId].push_back({ childId, weight });
    }

    GetMaxLengthRecursive(1);
    std::cout << sMaxLength;

    return 0;
}