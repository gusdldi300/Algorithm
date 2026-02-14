#include <iostream>
#include <climits>

#define MAX_PIPES_COUNT (361U)
#define MAX_LENGTH (100001U)

int main()
{
    unsigned int targetLength;
    unsigned int pipesCount;

    std::cin >> targetLength >> pipesCount;

    unsigned int maxCapacites[MAX_LENGTH] = { 0, };
    maxCapacites[0] = UINT_MAX;

    for (unsigned int pipe = 0; pipe < pipesCount; ++pipe)
    {
        unsigned int pipeLength;
        unsigned int pipeCapacity;
        std::cin >> pipeLength >> pipeCapacity;

        for (unsigned int length = targetLength; length >= pipeLength; --length)
        {
            maxCapacites[length] = std::max(maxCapacites[length],
                                            std::min(pipeCapacity, maxCapacites[length - pipeLength]));
        }
    }

    std::cout << maxCapacites[targetLength];

    return 0;
}