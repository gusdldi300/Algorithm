
#include <iostream>

enum class Bridge : unsigned int
{
    First = 0,
    Second
};

#define MAX_BRIDGES_COUNT (2U)
#define MAX_BRIDGE_SIZE (101U)
#define MAX_PATH_STRING_SIZE (21U)

static unsigned int sPathCases[MAX_BRIDGES_COUNT][MAX_PATH_STRING_SIZE][MAX_BRIDGE_SIZE] = { 0, };

static std::string sPathString;
static std::string sBridges[MAX_BRIDGES_COUNT];

static unsigned int GetBridgePathCasesRecursive(unsigned int bridgeIndex, unsigned int pathIndex, Bridge turn)
{
    if (pathIndex == sPathString.size())
    {
        return 1;
    }
    
    if (bridgeIndex == sBridges[0].size())
    {
        return 0;
    }

    unsigned int turnIndex = static_cast<unsigned int>(turn);

    if (sPathCases[turnIndex][pathIndex][bridgeIndex] > 0)
    {
        return sPathCases[turnIndex][pathIndex][bridgeIndex];
    }

    unsigned int maxPathCase = 0;

    for (unsigned int i = bridgeIndex; i < sBridges[0].size(); ++i)
    {
        if (sBridges[turnIndex][i] == sPathString[pathIndex])
        {
            unsigned int pathCase = GetBridgePathCasesRecursive(i + 1, pathIndex + 1, turn == Bridge::First ? Bridge::Second : Bridge::First);
            
            maxPathCase += pathCase;
        }
    }

    sPathCases[turnIndex][pathIndex][bridgeIndex] = maxPathCase;

    return maxPathCase;
}

int main()
{
    std::cin >> sPathString >> sBridges[0] >> sBridges[1];
    
    unsigned int firstBridgeStartCase = GetBridgePathCasesRecursive(0, 0, Bridge::First);
    unsigned int secondBridgeStartCase = GetBridgePathCasesRecursive(0, 0, Bridge::Second);

    std::cout << (firstBridgeStartCase + secondBridgeStartCase);

    return 0;
}