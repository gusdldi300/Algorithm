
#include <iostream>

#define MAX_TILE_LENGTH (1000001U)
#define DIVIDER (15746U)

unsigned int sTileCounts[MAX_TILE_LENGTH] = { 0, };

int main()
{
    unsigned int targetLength = 0;
    std::cin >> targetLength;

    sTileCounts[1] = 1;
    sTileCounts[2] = 2;

    for (unsigned int length = 3; length < MAX_TILE_LENGTH; ++length)
    {
        sTileCounts[length] = (sTileCounts[length - 2] + sTileCounts[length - 1]) % DIVIDER;
    }

    std::cout << sTileCounts[targetLength];

    return 0;
}