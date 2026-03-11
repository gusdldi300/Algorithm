#include <string>
#include <iostream>

#define MAX_STRING_SIZE (1001U)

int main()
{
    std::string firstString;
    std::string secondString;

    std::cin >> firstString >> secondString;

    unsigned int lcsLengths[MAX_STRING_SIZE][MAX_STRING_SIZE] = { 0, };
    std::string lcs;

    for (unsigned int firstIndex = 0; firstIndex < firstString.size(); ++firstIndex)
    {
        for (unsigned int secondIndex = 0; secondIndex < secondString.size(); ++secondIndex)
        {
            if (firstString[firstIndex] == secondString[secondIndex])
            {
                lcs.push_back(firstString[firstIndex]);

                lcsLengths[firstIndex + 1][secondIndex + 1] = lcsLengths[firstIndex][secondIndex] + 1;
            }
            else
            {
                lcsLengths[firstIndex + 1][secondIndex + 1] = std::max(lcsLengths[firstIndex][secondIndex + 1], lcsLengths[firstIndex + 1][secondIndex]);
            }
        }
    }

    std::cout << lcsLengths[firstString.size()][secondString.size()];

    return 0;
}