
#include <iostream>
#include <climits>
#include <stack>

#define MAX_SOURCES_COUNT (1000U)

static unsigned int sSources[MAX_SOURCES_COUNT];
static unsigned int sAscendLastIndexes[MAX_SOURCES_COUNT];
static unsigned int sAscendLengths[MAX_SOURCES_COUNT] = { 0, };

int main()
{
    unsigned int sourceCount;
    std::cin >> sourceCount;

    for (unsigned int i = 0; i < sourceCount; ++i)
    {
        std::cin >> sSources[i];
        
        sAscendLastIndexes[i] = UINT_MAX;
    }

    unsigned int longestLengthIndex = 0;
    unsigned int longestLength = 0;
    
    sAscendLengths[0] = 1;
    for (unsigned int i = 1; i < sourceCount; ++i)
    {
        for (unsigned int j = 0; j < i; ++j)
        {
            if (sSources[i] > sSources[j])
            {
                if (sAscendLengths[i] < sAscendLengths[j])
                {
                    sAscendLengths[i] = sAscendLengths[j];
                    sAscendLastIndexes[i] = j;

                }
            }
        }

        sAscendLengths[i]++;

        if (longestLength < sAscendLengths[i])
        {
            longestLength = sAscendLengths[i];
            longestLengthIndex = i;
        }
    }

    std::cout << sAscendLengths[longestLengthIndex] << std::endl;
    
    std::stack<unsigned int> indexStack;
    unsigned int ascendIndex = longestLengthIndex;
    while (ascendIndex < UINT_MAX)
    {
        indexStack.push(sSources[ascendIndex]);

        ascendIndex = sAscendLastIndexes[ascendIndex];
    }

    while (indexStack.empty() == false)
    {
        unsigned int index = indexStack.top();
        indexStack.pop();

        std::cout << index << " ";
    }

    return 0;
}