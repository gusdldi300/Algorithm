
#include <unordered_map>
#include <iostream>

#include "Edge.h"
#include "Kruskal.h"

int main()
{
    unsigned int nodesCount;
    unsigned int edgesCount;

    std::cin >> nodesCount >> edgesCount;

    std::vector<unsigned int> nodes;
    nodes.reserve(nodesCount);

    std::vector<Edge> edges;
    edges.reserve(edgesCount);

    for (unsigned int i = 0; i < nodesCount; ++i)
    {
        nodes.push_back(i + 1);
    }

    for (unsigned int i = 0; i < edgesCount; ++i)
    {
        unsigned int firstNode;
        unsigned int secondNode;
        int weight;

        std::cin >> firstNode >> secondNode >> weight;

        Edge edge(firstNode, secondNode, weight);
        edges.push_back(edge);
    }

    std::vector<Edge> mst;
    mst.reserve(nodesCount);

    Kruskal::GetMST(nodes, edges, &mst);

    int minTotalWeight = 0;
    for (unsigned int i = 0; i < mst.size(); ++i)
    {
        minTotalWeight += mst[i].GetWeight();
    }

    std::cout << minTotalWeight;

    return 0;
}
