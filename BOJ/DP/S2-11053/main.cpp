
#include <iostream>
#include <cassert>

#define MAX_SEQUENCE_SIZE (1000)

static unsigned int sSmallerCounts[MAX_SEQUENCE_SIZE] = { 0, };
static unsigned int sSequence[MAX_SEQUENCE_SIZE] = { 0, };

int main()
{
    int sequenceSize = 0;
    std::cin >> sequenceSize;
    assert(sequenceSize >= 1 && sequenceSize <= MAX_SEQUENCE_SIZE);

    for (unsigned int i = 0; i < sequenceSize; ++i)
    {
        std::cin >> sSequence[i];
    }

    unsigned int longestSubSequenceSize = 0;
    for (int sequencIndex = 0; sequencIndex < sequenceSize; ++sequencIndex)
    {
        unsigned int longestCount = 0;
        unsigned int number = sSequence[sequencIndex];
        for (int countIndex = sequencIndex - 1; countIndex >= 0; --countIndex)
        {
            if (number > sSequence[countIndex] && sSmallerCounts[countIndex] > longestCount)
            {
                longestCount = sSmallerCounts[countIndex];
            }
        }

        sSmallerCounts[sequencIndex] = longestCount + 1;
        if (sSmallerCounts[sequencIndex] > longestSubSequenceSize)
        {
            longestSubSequenceSize = sSmallerCounts[sequencIndex];
        }
    }

    std::cout << longestSubSequenceSize;

    return 0;
}