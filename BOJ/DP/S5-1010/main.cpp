
#include <iostream>
#include <vector>

#define MAX_SITE_COUNT (30U)

unsigned int GetBridgeCombinationRecursive(unsigned int westSiteCount, unsigned int eastSiteCount, unsigned int cache[][MAX_SITE_COUNT])
{
    if (westSiteCount == 0 || westSiteCount == eastSiteCount)
    {
        return 1;
    }

    if (cache[eastSiteCount][westSiteCount] > 0)
    {
        return cache[eastSiteCount][westSiteCount];
    }

    int bridgeCombination = GetBridgeCombinationRecursive(westSiteCount - 1, eastSiteCount - 1, cache) +
        GetBridgeCombinationRecursive(westSiteCount, eastSiteCount - 1, cache);

    cache[eastSiteCount][westSiteCount] = bridgeCombination;

    return bridgeCombination;
}

int main()
{
    std::vector<unsigned int> results;
    
    unsigned int cache[MAX_SITE_COUNT][MAX_SITE_COUNT] = { 0, };
    unsigned int maxTestCaseCount = 0;

    std::cin >> maxTestCaseCount;

    // Top-down
    /*
    for (unsigned int testCaseCount = 0; testCaseCount < maxTestCaseCount; ++testCaseCount)
    {
        unsigned int westSiteCount = 0;
        unsigned int eastSiteCount = 0;

        std::cin >> westSiteCount >> eastSiteCount;
        
        results.push_back(GetBridgeCombinationRecursive(westSiteCount, eastSiteCount, cache));
    }

    for (unsigned int result : results)
    {
        std::cout << result << std::endl;
    }
    */

    // Buttom-up
    for (unsigned int i = 0; i < MAX_SITE_COUNT; ++i)
    {
        cache[i][0] = 1;
        cache[i][i] = 1;
    }

    for (unsigned int row = 2; row < MAX_SITE_COUNT; ++row)
    {
        for (unsigned int col = 1; col < row; ++col)
        {
            cache[row][col] = cache[row - 1][col - 1] + cache[row - 1][col];
        }
    }

    for (unsigned int testCaseCount = 0; testCaseCount < maxTestCaseCount; ++testCaseCount)
    {
        unsigned int westSiteCount = 0;
        unsigned int eastSiteCount = 0;

        std::cin >> westSiteCount >> eastSiteCount;
        std::cout << cache[eastSiteCount][westSiteCount] << std::endl;
    }

    return 0;
}
