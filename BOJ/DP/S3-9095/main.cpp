
#include <cassert>
#include <iostream>

#define MAX_TARGET_NUMBER (11U)

int main()
{
    unsigned int numberOfAddedMethods[MAX_TARGET_NUMBER] = { 0, };
    
    unsigned int caseCount = 0;
    std::cin >> caseCount;

    assert(caseCount < MAX_TARGET_NUMBER);

    numberOfAddedMethods[1] = 1;
    numberOfAddedMethods[2] = 2;
    numberOfAddedMethods[3] = 4;

    for (unsigned int number = 4; number < MAX_TARGET_NUMBER; ++number)
    {
        numberOfAddedMethods[number] = numberOfAddedMethods[number - 1] + numberOfAddedMethods[number - 2] + numberOfAddedMethods[number - 3];
    }


    unsigned int targetNumber = 0;
    for (unsigned int i = 0; i < caseCount; ++i)
    {
        std::cin >> targetNumber;
        std::cout << numberOfAddedMethods[targetNumber] << std::endl;
    }

    return 0;
}