
#include <cmath>
#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int liquidsCount;
    std::cin >> liquidsCount;

    std::vector<long long> liquidsAscend;
    for (unsigned int i = 0; i < liquidsCount; ++i)
    {
        long long liquid;
        std::cin >> liquid;

        liquidsAscend.push_back(liquid);
    }

    std::sort(liquidsAscend.begin(), liquidsAscend.end());

    unsigned int leftIndex = 0;
    unsigned int rightIndex = liquidsAscend.size() - 1;
    
    long long minMixedLiquid = LLONG_MAX;
    while (leftIndex < rightIndex)
    {
        long long mixedLiquid = liquidsAscend[leftIndex] + liquidsAscend[rightIndex];
        if (mixedLiquid == 0)
        {
            minMixedLiquid = 0;
            
            break;
        }

        if (std::abs(mixedLiquid) < std::abs(minMixedLiquid))
        {
            minMixedLiquid = mixedLiquid;
        }

        if (mixedLiquid > 0)
        {
            --rightIndex;
        }
        else
        {
            ++leftIndex;
        }
    }

    std::cout << minMixedLiquid;

    return 0;
}