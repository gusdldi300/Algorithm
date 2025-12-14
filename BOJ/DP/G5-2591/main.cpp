
#include <iostream>
#include <string>

#define MAX_DIGITS (41U)
#define MAX_NUMBER (34)

static unsigned int sCases[MAX_DIGITS];

int main()
{
    std::string numberString;
    std::cin >> numberString;

    bool bWrongNumber = false;

    sCases[0] = 1;
    sCases[1] = 1;

    for (unsigned int i = 1; i < numberString.size(); ++i)
    {
        if (numberString[i] != '0')
        {
            sCases[i + 1] = sCases[i];
        }

        char twoDigitNumber = ((numberString[i - 1] - '0') * 10) + (numberString[i] - '0');

        if (numberString[i - 1] != '0' && twoDigitNumber <= MAX_NUMBER)
        {
            sCases[i + 1] += sCases[i - 1];
        }
    }
    
    std::cout << sCases[numberString.size()];
    
    return 0;
}