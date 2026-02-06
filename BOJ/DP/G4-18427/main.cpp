
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#define MAX_STUDENTS_COUNT (51U)
#define MAX_BLOCKS_COUNT (11U)
#define MAX_TARGET_HEIGHT (1001U)

#define DIVISOR (10007U)

static unsigned int sStudentsCount;
static unsigned int sBlockHeightsCount;
static unsigned int sTargetHeight;

static std::vector<unsigned int> sStudentBlockHeights[MAX_STUDENTS_COUNT];

/*
static unsigned int sBlockHeightCases[MAX_STUDENTS_COUNT][MAX_TARGET_HEIGHT] = { 0, };

static unsigned int GetBlockCaseCountRecursive(unsigned int student, unsigned int height)
{
    if (height > sTargetHeight)
    {
        return 0;
    }
    else if (height == sTargetHeight)
    {  
        return 1;
    }

    if (student >= sStudentsCount)
    {
        return 0;
    }

    if (sBlockHeightCases[student][height] > 0)
    {
        return sBlockHeightCases[student][height];
    }

    unsigned int totalCount = 0;
    for (unsigned int blockHeight : sStudentBlocks[student])
    {
        totalCount += GetBlockCaseCountRecursive(student + 1, height + blockHeight);
    }

    totalCount %= DIVISOR;

    sBlockHeightCases[student][height] = totalCount;
    return totalCount;
}
*/

int main()
{
    std::cin >> sStudentsCount >> sBlockHeightsCount >> sTargetHeight;
    std::cin.ignore();

    for (unsigned int i = 0; i < sStudentsCount; ++i)
    {
        std::string inputString;
        std::getline(std::cin, inputString);

        std::stringstream stringStream(inputString);

        sStudentBlockHeights[i].push_back(0);

        while (true)
        {
            std::string blockString;
            std::getline(stringStream, blockString, ' ');

            if (stringStream.fail())
            {
                break;
            }

            sStudentBlockHeights[i].push_back(static_cast<unsigned int>(std::stoi(blockString)));
        }
    }

    std::unordered_map<unsigned int, unsigned int> blockHeightCounts[MAX_STUDENTS_COUNT];
    for (unsigned int blockHeight : sStudentBlockHeights[0])
    {
        blockHeightCounts[0].insert(std::make_pair(blockHeight, 1U));
    }

    for (unsigned int i = 1; i < sStudentsCount; ++i)
    {
        for (unsigned int j = 0; j < sStudentBlockHeights[i].size(); ++j)
        {
            unsigned int blockHeight = sStudentBlockHeights[i][j];

            for (auto lastHeightCount : blockHeightCounts[i - 1])
            {
                unsigned int heightSum = blockHeight + lastHeightCount.first;
                if (heightSum > sTargetHeight)
                {
                    continue;
                }

                if (blockHeightCounts[i].find(heightSum) != blockHeightCounts[i].end())
                {
                    blockHeightCounts[i][heightSum] = (blockHeightCounts[i][heightSum] + lastHeightCount.second) % DIVISOR;

                    continue;
                }

                blockHeightCounts[i].insert(std::make_pair(heightSum, lastHeightCount.second));
            }
        }
    }

    //unsigned int totalCount = GetBlockCaseCountRecursive(0, 0);
    std::cout << blockHeightCounts[sStudentsCount - 1][sTargetHeight];

    return 0;
}