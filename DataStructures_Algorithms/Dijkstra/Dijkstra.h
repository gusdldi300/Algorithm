#pragma once

#include <list>
#include <queue>

class Dijkstra
{
public:
    struct Result
    {
        std::list<unsigned int> ShortestPath;
        unsigned int ShortestDistance;
    };

private:
    struct Edge
    {
        unsigned int StartID;
        unsigned int EndID;
        unsigned int Distance;

        bool operator<(const Edge& other) const
        {
            return Distance > other.Distance;
        }
    };

public:
    // Returns UINT_MAX, if cannot find destination
    static Result GetShortestPathAndDistance(unsigned int startID, unsigned int endID, unsigned int** weightedGraph, const unsigned int IDS_SIZE);

private:
    static void AddNewEdgeAndUpdatePath(unsigned int startID, unsigned int endID, unsigned int accumulatedDistance, std::priority_queue<Edge>* outDistanceAscendQueue, unsigned int* outShortestDistances, unsigned int* outPaths);
};

