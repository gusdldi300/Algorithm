
#include <cassert>
#include <queue>

#include "Dijkstra.h"

void Dijkstra::AddNewEdgeAndUpdatePath(unsigned int startID, unsigned int endID, unsigned int accumulatedDistance, std::priority_queue<Edge>* outDistanceAscendQueue, unsigned int* outShortestDistances, unsigned int* outLastPaths)
{
    assert(outDistanceAscendQueue != nullptr);
    assert(outLastPaths != nullptr);

    outLastPaths[endID] = startID;
    outShortestDistances[endID] = accumulatedDistance;

    Edge newEdge = { startID, endID, accumulatedDistance };
    outDistanceAscendQueue->push(newEdge);
}

Dijkstra::Result Dijkstra::GetShortestPathAndDistance(unsigned int startID, unsigned int endID, unsigned int** weightedGraph, const unsigned int IDS_SIZE)
{
    assert(weightedGraph != nullptr);

    Result result;
    
    if (startID == endID)
    {
        result.ShortestDistance = 0;
        result.ShortestPath.push_back(startID);

        return result;
    }

    unsigned int* shortestDistances = new unsigned int[IDS_SIZE];
    memset(shortestDistances, -1, sizeof(unsigned int) * IDS_SIZE);

    unsigned int* lastPaths = new unsigned int[IDS_SIZE];
    memset(lastPaths, -1, sizeof(unsigned int) * IDS_SIZE);
    
    bool* bVisiteds = new bool[IDS_SIZE];
    memset(bVisiteds, static_cast<int>(false), sizeof(bool) * IDS_SIZE);

    std::priority_queue<Edge> distanceAscendQueue;
    for (unsigned int toID = 0; toID < IDS_SIZE; ++toID)
    {
        if (weightedGraph[startID][toID] == 0)
        {
            continue;
        }

        AddNewEdgeAndUpdatePath(startID, toID, weightedGraph[startID][toID], &distanceAscendQueue, shortestDistances, lastPaths);
    }

    shortestDistances[startID] = 0;
    bVisiteds[startID] = true;
    lastPaths[startID] = startID;

    while (distanceAscendQueue.empty() == false)
    {
        Edge edge = distanceAscendQueue.top();
        distanceAscendQueue.pop();

        unsigned int curID = edge.EndID;
        if (bVisiteds[curID])
        {
            continue;
        }

        bVisiteds[curID] = true;

        if (curID == endID)
        {
            break;
        }

        for (unsigned int toID = 0; toID < IDS_SIZE; ++toID)
        {
            if (weightedGraph[curID][toID] == 0)
            {
                continue;
            }

            assert(shortestDistances[curID] != UINT_MAX);
            unsigned int accumulatedDistance = shortestDistances[curID] + weightedGraph[curID][toID];
            if (accumulatedDistance >= shortestDistances[toID])
            {
                continue;
            }

            AddNewEdgeAndUpdatePath(curID, toID, accumulatedDistance, &distanceAscendQueue, shortestDistances, lastPaths);
        }
    }

    if (bVisiteds[endID] == false)
    {
        result.ShortestDistance = UINT_MAX;
    }
    else
    {
        result.ShortestDistance = shortestDistances[endID];

        unsigned int pathID = endID;
        while (pathID != startID)
        {
            result.ShortestPath.push_front(pathID);

            pathID = lastPaths[pathID];
        }

        result.ShortestPath.push_front(startID);
    }

    delete[] shortestDistances;
    delete[] bVisiteds;
    delete[] lastPaths;

    return result;
}
