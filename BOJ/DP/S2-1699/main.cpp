
#include <iostream>
#include <cmath>
#include <climits>

#define MAX_NUMBER (100001U)

static unsigned int sMinSquareTerms[MAX_NUMBER] = { 0, };

int main()
{
    unsigned int targetNumber = 0;

    sMinSquareTerms[1] = 1;
    
    std::cin >> targetNumber;
    
    for (unsigned int number = 2; number <= targetNumber; ++number)
    {
        unsigned int sqrtNumber = static_cast<unsigned int>(sqrt(number));
        sMinSquareTerms[number] = UINT_MAX;

        for (unsigned int powIndex = 1; powIndex <= sqrtNumber; ++powIndex)
        {
            sMinSquareTerms[number] = std::min(sMinSquareTerms[number], sMinSquareTerms[number - (powIndex * powIndex)] + 1);
        }
    }

    std::cout << sMinSquareTerms[targetNumber];
    
    return 0;
}