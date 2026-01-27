
#include <climits>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

#define MAX_MAP_SIZE (101U)
#define MAX_MOVE_DIRECTIONS_COUNT (4U)

#define MAX_WIRE_LENGTH (MAX_MAP_SIZE * MAX_MAP_SIZE)

static const std::pair<int, int> MOVE_DIRECTIONS[MAX_MOVE_DIRECTIONS_COUNT] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static int sMapRowSize;
static int sMapColSize;

// Returns wire length
static unsigned int SetShortestWire(pair<int, int> startPosition, pair<int, int> endPosition, bool outWireMap[][MAX_MAP_SIZE])
{
    map<pair<int, int>, pair<int, int>> visitedPaths;
    
    queue<std::pair<int, int>> positionQueue;
    positionQueue.push(startPosition);
    visitedPaths.insert(make_pair(startPosition, startPosition));

    bool bFound = false;
    while (positionQueue.empty() == false)
    {
        std::pair<int, int> position = positionQueue.front();
        positionQueue.pop();

        if (position == endPosition)
        {
            bFound = true;

            break;
        }
        
        for (unsigned int dirIndex = 0; dirIndex < MAX_MOVE_DIRECTIONS_COUNT; ++dirIndex)
        {
            std::pair<int, int> nextPosition = position;
            nextPosition.first += MOVE_DIRECTIONS[dirIndex].first;
            nextPosition.second += MOVE_DIRECTIONS[dirIndex].second;

            if (nextPosition.first < 0 || nextPosition.first >= sMapRowSize ||
                nextPosition.second < 0 || nextPosition.second >= sMapColSize)
            {
                continue;
            }

            if (outWireMap[nextPosition.first][nextPosition.second] || visitedPaths.find(nextPosition) != visitedPaths.end())
            {
                continue;
            }

            visitedPaths.insert(make_pair(nextPosition, position));
            positionQueue.push(nextPosition);
        }
    }

    if (bFound == false)
    {
        return MAX_WIRE_LENGTH + 1;
    }

    // Set wire on map
    std::pair<int, int> position = endPosition;
    outWireMap[position.first][position.second] = true;

    unsigned int wireLength = 0;

    while (true)
    {
        std::pair<int, int> lastPosition = visitedPaths[position];
        if (position == lastPosition)
        {
            break;
        }

        outWireMap[lastPosition.first][lastPosition.second] = true;
        position = lastPosition;

        wireLength++;
    }

    return wireLength;
}

unsigned int GetShortestWireLength(pair<int, int> startPosition, pair<int, int> endPosition, pair<int, int> otherStartPosition, pair<int, int> otherEndPosition)
{
    bool aWireFirstMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };
    aWireFirstMap[otherStartPosition.first][otherStartPosition.second] = true;
    aWireFirstMap[otherEndPosition.first][otherEndPosition.second] = true;

    unsigned int wireLength = SetShortestWire(startPosition, endPosition, aWireFirstMap);

    aWireFirstMap[otherStartPosition.first][otherStartPosition.second] = false;
    aWireFirstMap[otherEndPosition.first][otherEndPosition.second] = false;
    wireLength += SetShortestWire(otherStartPosition, otherEndPosition, aWireFirstMap);

    return wireLength;
}

int main()
{
    std::cin >> sMapColSize >> sMapRowSize;
    sMapColSize++;
    sMapRowSize++;

    pair<int, int> aStartPosition;
    pair<int, int> aEndPosition;

    std::cin >> aStartPosition.second >> aStartPosition.first
             >> aEndPosition.second >> aEndPosition.first;

    pair<int, int> bStartPosition;
    pair<int, int> bEndPosition;

    std::cin >> bStartPosition.second >> bStartPosition.first
             >> bEndPosition.second >> bEndPosition.first;


    unsigned int aWireFirstLength = GetShortestWireLength(aStartPosition, aEndPosition, bStartPosition, bEndPosition);
    unsigned int bWireFirstLength = GetShortestWireLength(bStartPosition, bEndPosition, aStartPosition, aEndPosition);

    if (aWireFirstLength >= MAX_WIRE_LENGTH && bWireFirstLength >= MAX_WIRE_LENGTH)
    {
        std::cout << "IMPOSSIBLE";
    }
    else
    {
        std::cout << (std::min(aWireFirstLength, bWireFirstLength));
    }

    return 0;
}