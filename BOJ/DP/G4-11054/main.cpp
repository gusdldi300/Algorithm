
#include <iostream>

#define MAX_SOURCE_COUNT (1001U)

static unsigned int sSequence[MAX_SOURCE_COUNT] = { 0, };
static unsigned int sSubsequenceLengths[2][MAX_SOURCE_COUNT];

int main()
{
    unsigned int sourceCount;
    std::cin >> sourceCount;

    for (int i = 0; i < sourceCount; ++i)
    {
        unsigned int source;
        std::cin >> source;

        sSequence[i] = source;

        sSubsequenceLengths[0][i] = 1;
        sSubsequenceLengths[1][i] = 1;
    }

    for (int i = 1; i < sourceCount; ++i)
    {
        for (int j = i - 1; j >= 0; --j)
        {
            if (sSequence[i] > sSequence[j])
            {
                sSubsequenceLengths[0][i] = std::max(sSubsequenceLengths[0][i], sSubsequenceLengths[0][j] + 1);
            }
        }
        
        int descendStartIndex = sourceCount - i - 1;
        for (int j = descendStartIndex + 1; j < sourceCount; ++j)
        {
            if (sSequence[descendStartIndex] > sSequence[j])
            {
                sSubsequenceLengths[1][descendStartIndex] = std::max(sSubsequenceLengths[1][descendStartIndex], sSubsequenceLengths[1][j] + 1);
            }
        }
    }
    
    unsigned int maxLength = 0;
    for (int i = 0; i < sourceCount; ++i)
    {
        maxLength = std::max(maxLength, sSubsequenceLengths[0][i] + sSubsequenceLengths[1][i]);
    }

    std::cout << maxLength - 1;

    return 0;
}