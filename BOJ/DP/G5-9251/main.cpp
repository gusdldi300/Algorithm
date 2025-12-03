
#include <iostream>
#include <unordered_map>
#include <string>

#define MAX_STRING_SIZE (1000U)

static unsigned int sLengths[MAX_STRING_SIZE][MAX_STRING_SIZE] = { 0, };

int main()
{
    std::string firstString;
    std::string secondString;

    std::cin >> firstString >> secondString;

    for (unsigned int j = 0; j < secondString.size(); j++)
    {
        if (secondString[j] == firstString[0])
        {
            sLengths[0][j] = 1;
        }
    }

    for (int i = 1; i < firstString.size(); i++)
    {
        unsigned int maxLength = 0;
        for (int j = 0; j < secondString.size(); j++)
        {
            if (secondString[j] == firstString[i])
            {
                sLengths[i][j] = maxLength + 1;
            }
            else
            {
                sLengths[i][j] = sLengths[i - 1][j];
            }

            maxLength = std::max(maxLength, sLengths[i - 1][j]);
        }
    }

    unsigned int maxPrintLength = 0;
    for (unsigned int i = 0; i < secondString.size(); i++)
    {
        maxPrintLength = std::max(maxPrintLength, sLengths[firstString.size() - 1][i]);
    }

    std::cout << maxPrintLength;

    return 0;
}