
#include <iostream>
#include <unordered_map>

#define MAX_PIPES_COUNT (361U)

int main()
{
    unsigned int targetLength;
    unsigned int pipesCount;
    
    std::cin >> targetLength >> pipesCount;

    std::unordered_map<unsigned int, unsigned int> lastLengthMaxCapacityMap;
    std::unordered_map<unsigned int, unsigned int> lengthMaxCapacityMap;

    unsigned int pipeLength;
    unsigned int pipeCapacity;

    std::cin >> pipeLength >> pipeCapacity;
    if (pipeLength <= targetLength)
    {
        lastLengthMaxCapacityMap.insert(std::pair<unsigned int, unsigned int>(pipeLength, pipeCapacity));
    }
    
    for (unsigned int pipe = 1; pipe < pipesCount; ++pipe)
    {
        std::cin >> pipeLength >> pipeCapacity;
        
        if (pipeLength > targetLength)
        {
            continue;
        }

        unsigned int newPipeCapacity = pipeCapacity;
        if (lengthMaxCapacityMap.find(pipeLength) != lengthMaxCapacityMap.end())
        {
            newPipeCapacity = std::max(newPipeCapacity, lengthMaxCapacityMap[pipeLength]);
        }

        lengthMaxCapacityMap[pipeLength] = newPipeCapacity;

        for (auto pipeInfo : lastLengthMaxCapacityMap)
        {
            unsigned int newPipeCapacity = pipeInfo.second;
            if (lengthMaxCapacityMap.find(pipeInfo.first) != lengthMaxCapacityMap.end())
            {
                newPipeCapacity = std::max(newPipeCapacity, lengthMaxCapacityMap[pipeInfo.first]);
            }

            lengthMaxCapacityMap[pipeInfo.first] = newPipeCapacity;

            unsigned int connectedLength = pipeInfo.first + pipeLength;
            if (connectedLength > targetLength)
            {
                continue;
            }

            unsigned int connectedPipeCapacity = std::min(lastLengthMaxCapacityMap[pipeInfo.first], pipeCapacity);
            if (lengthMaxCapacityMap.find(connectedLength) != lengthMaxCapacityMap.end())
            {
                connectedPipeCapacity = std::max(connectedPipeCapacity, lengthMaxCapacityMap[connectedLength]);
            }

            lengthMaxCapacityMap[connectedLength] = connectedPipeCapacity;
        }

        std::swap(lastLengthMaxCapacityMap, lengthMaxCapacityMap);
        lengthMaxCapacityMap.clear();
    }

    std::cout << lastLengthMaxCapacityMap[targetLength];

    return 0;
}