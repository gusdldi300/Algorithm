
#include <iostream>

#define MAX_DIGITS (33334U)
#define DIVISOR (1000000009)

static unsigned int sCounts[MAX_DIGITS] = { 0, };

int main()
{
    unsigned int targetDigit = 0;
    std::cin >> targetDigit;

    sCounts[1] = 1;
    for (unsigned int digit = 2; digit <= targetDigit; ++digit)
    {
        sCounts[digit] = (sCounts[digit - 1] * 3) % DIVISOR;
    }
    
    std::cout << ((sCounts[targetDigit - 1] * 2) % DIVISOR);

    return 0;
}