
#include <cassert>
#include <cstring>

#include "Dijkstra.h"



int main()
{
    const unsigned int IDS_SIZE = 6U;

    unsigned int** weightedGraph = new unsigned int*[IDS_SIZE];
    for (unsigned int row = 0; row < IDS_SIZE; ++row)
    {
        weightedGraph[row] = new unsigned int[IDS_SIZE];
        memset(weightedGraph[row], 0, sizeof(unsigned int) * IDS_SIZE);
    }

    // Create graph
    {
        weightedGraph[0][1] = 2;
        weightedGraph[0][2] = 3;

        weightedGraph[1][0] = 2;
        weightedGraph[1][3] = 1;
        weightedGraph[1][5] = 6;

        weightedGraph[2][0] = 3;
        weightedGraph[2][3] = 2;

        weightedGraph[3][1] = 1;
        weightedGraph[3][2] = 2;
        weightedGraph[3][4] = 2;

        weightedGraph[4][3] = 2;
        weightedGraph[4][5] = 1;

        weightedGraph[5][1] = 6;
        weightedGraph[5][4] = 1;
    }

    Dijkstra::Result result = Dijkstra::GetShortestPathAndDistance(0, 5, weightedGraph, IDS_SIZE);
    assert(result.ShortestDistance == 6);

    std::list<unsigned int>::const_iterator constIter = result.ShortestPath.begin();
    assert(*constIter++ == 0);
    assert(*constIter++ == 1);
    assert(*constIter++ == 3);
    assert(*constIter++ == 4);
    assert(*constIter == 5);

    for (unsigned int row = 0; row < IDS_SIZE; ++row)
    {
        delete[] weightedGraph[row];
    }
    delete[] weightedGraph;

    return 0;
}