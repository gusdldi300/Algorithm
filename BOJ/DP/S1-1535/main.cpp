
#include <iostream>

#define MAX_NUMBER_OF_DIGITS (101U)
#define MAX_START_NUMBER (10U)
#define LAST_START_NUMBER (MAX_START_NUMBER - 1)

#define COUNT_DIVISOR (1000000000U)

// row: Number of digits
// col: Start number
static unsigned int sCache[MAX_NUMBER_OF_DIGITS][MAX_START_NUMBER] = { 0, };

int main()
{
    unsigned int targetDigit = 0;
    std::cin >> targetDigit;

    for (unsigned int startNumber = 0; startNumber < MAX_START_NUMBER; ++startNumber)
    {
        sCache[1][startNumber] = 1;
    }

    for (unsigned int digit = 2; digit <= targetDigit; ++digit)
    {
        unsigned int lastDigit = digit - 1;

        sCache[digit][0] = sCache[lastDigit][1];
        sCache[digit][LAST_START_NUMBER] = sCache[lastDigit][LAST_START_NUMBER - 1];

        for (unsigned int startNumber = 1; startNumber < LAST_START_NUMBER; ++startNumber)
        {
            sCache[digit][startNumber] = (sCache[lastDigit][startNumber - 1] + sCache[lastDigit][startNumber + 1]) % COUNT_DIVISOR;
        }
    }

    unsigned int count = 0;
    for (unsigned int startNumber = 1; startNumber < MAX_START_NUMBER; ++startNumber)
    {
        count += sCache[targetDigit][startNumber];
        count %= COUNT_DIVISOR;
    }

    std::cout << count;

    return 0;
}