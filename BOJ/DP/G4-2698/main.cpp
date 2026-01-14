#include <iostream>

#define MAX_SEQUENCE_SIZE (101U)
#define MAX_ADJACENT_BITS_SIZE (MAX_SEQUENCE_SIZE)
#define START_BITS_SIZE (2U)

static unsigned int sAdjacentBits[MAX_SEQUENCE_SIZE][MAX_ADJACENT_BITS_SIZE][START_BITS_SIZE] = { 0, };

int main()
{
    sAdjacentBits[2][0][0] = 2;
    sAdjacentBits[2][0][1] = 1;

    sAdjacentBits[2][1][1] = 1;
    
    for (unsigned int sequenceSize = 3; sequenceSize < MAX_SEQUENCE_SIZE; ++sequenceSize)
    {
        unsigned int lastSequenceSize = sequenceSize - 1;
        sAdjacentBits[sequenceSize][0][0] = sAdjacentBits[lastSequenceSize][0][0] +
                                           sAdjacentBits[lastSequenceSize][0][1];

        sAdjacentBits[sequenceSize][0][1] = sAdjacentBits[lastSequenceSize][0][0];

        for (unsigned int adjacentBits = 1; adjacentBits < sequenceSize - 1; ++adjacentBits)
        {
            sAdjacentBits[sequenceSize][adjacentBits][0] = sAdjacentBits[lastSequenceSize][adjacentBits][0] +
                                                          sAdjacentBits[lastSequenceSize][adjacentBits][1];

            sAdjacentBits[sequenceSize][adjacentBits][1] = sAdjacentBits[lastSequenceSize][adjacentBits][0] +
                                                          sAdjacentBits[lastSequenceSize][adjacentBits - 1][1];

        }

        sAdjacentBits[sequenceSize][sequenceSize - 1][1] = 1;
    }

    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int i = 0; i < testsCount; ++i)
    {
        unsigned int adjacentBits;
        unsigned int sequenceSize;
        
        std::cin >> sequenceSize >> adjacentBits;

        std::cout << (sAdjacentBits[sequenceSize][adjacentBits][0] + sAdjacentBits[sequenceSize][adjacentBits][1]) << '\n';
    }

    return 0;
}