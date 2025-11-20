
#include <algorithm>
#include <iostream>
#include <cassert>

#define MAX_TARGET_NUMBER (1000001U)

unsigned int sMinOperationCounts[MAX_TARGET_NUMBER] = { 0, };

int main()
{
    unsigned int targetNumber = 0;
    std::cin >> targetNumber;
    
    assert(targetNumber >= 1 && targetNumber < MAX_TARGET_NUMBER);

    sMinOperationCounts[1] = 0;
    sMinOperationCounts[2] = 1;
    sMinOperationCounts[3] = 1;

    for (unsigned int number = 4; number < MAX_TARGET_NUMBER; ++number)
    {
        sMinOperationCounts[number] = sMinOperationCounts[number - 1];

        if (number % 2 == 0)
        {
            sMinOperationCounts[number] = std::min(sMinOperationCounts[number], sMinOperationCounts[number / 2]);
        }
        
        if (number % 3 == 0)
        {
            sMinOperationCounts[number] = std::min(sMinOperationCounts[number], sMinOperationCounts[number / 3]);
        }

        sMinOperationCounts[number]++;
    }

    std::cout << sMinOperationCounts[targetNumber];

    return 0;
}