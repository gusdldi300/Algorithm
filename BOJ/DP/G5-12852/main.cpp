
#include <iostream>
#include <cassert>
#include <climits>

#define MAX_NUMBER (1000001U)
#define MIN_OPERATIONS_INDEX (0U)
#define LAST_NUMBER_INDEX (1U)

static unsigned int sMinOperations[MAX_NUMBER][2] = { 0, };

int main()
{
    unsigned int targetNumber = 0;
    std::cin >> targetNumber;

    for (unsigned int number = 4; number <= targetNumber; ++number)
    {
        sMinOperations[number][MIN_OPERATIONS_INDEX] = UINT_MAX;
    }

    sMinOperations[1][MIN_OPERATIONS_INDEX] = 0;

    sMinOperations[2][MIN_OPERATIONS_INDEX] = 1;
    sMinOperations[2][LAST_NUMBER_INDEX] = 1;

    sMinOperations[3][MIN_OPERATIONS_INDEX] = 1;
    sMinOperations[3][LAST_NUMBER_INDEX] = 1;

    for (unsigned int number = 4; number <= targetNumber; ++number)
    {
        unsigned int lastNumber = number - 1;

        sMinOperations[number][MIN_OPERATIONS_INDEX] = sMinOperations[lastNumber][MIN_OPERATIONS_INDEX];
        sMinOperations[number][LAST_NUMBER_INDEX] = lastNumber;

        lastNumber = number / 3;
        if (number % 3 == 0 && (sMinOperations[lastNumber][MIN_OPERATIONS_INDEX] < sMinOperations[number][MIN_OPERATIONS_INDEX]))
        {
            sMinOperations[number][MIN_OPERATIONS_INDEX] = sMinOperations[lastNumber][MIN_OPERATIONS_INDEX];
            sMinOperations[number][LAST_NUMBER_INDEX] = lastNumber;
        }

        lastNumber = number / 2;
        if (number % 2 == 0 && (sMinOperations[lastNumber][MIN_OPERATIONS_INDEX] < sMinOperations[number][MIN_OPERATIONS_INDEX]))
        {
            sMinOperations[number][MIN_OPERATIONS_INDEX] = sMinOperations[lastNumber][MIN_OPERATIONS_INDEX];
            sMinOperations[number][LAST_NUMBER_INDEX] = lastNumber;
        }

        sMinOperations[number][MIN_OPERATIONS_INDEX]++;
    }

    std::cout << sMinOperations[targetNumber][MIN_OPERATIONS_INDEX] << std::endl;

    unsigned int printNumber = targetNumber;
    assert(printNumber != 0);

    while (printNumber > 0)
    {
        std::cout << printNumber << " ";

        printNumber = sMinOperations[printNumber][LAST_NUMBER_INDEX];
    }

    return 0;
}