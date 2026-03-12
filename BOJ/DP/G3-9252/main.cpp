#include <iostream>
#include <stack>

#define MAX_STRING_SIZE (1001U)

int main()
{
    std::string firstString;
    std::string secondString;

    std::cin >> firstString >> secondString;

    unsigned int lcsLengths[MAX_STRING_SIZE][MAX_STRING_SIZE] = { 0, };

    for (unsigned int firstIndex = 0; firstIndex < firstString.size(); ++firstIndex)
    {
        for (unsigned int secondIndex = 0; secondIndex < secondString.size(); ++secondIndex)
        {
            if (firstString[firstIndex] == secondString[secondIndex])
            {
                lcsLengths[firstIndex + 1][secondIndex + 1] = lcsLengths[firstIndex][secondIndex] + 1;
            }
            else
            {
                lcsLengths[firstIndex + 1][secondIndex + 1] = std::max(lcsLengths[firstIndex][secondIndex + 1], lcsLengths[firstIndex + 1][secondIndex]);
            }
        }
    }

    std::stack<char> lcsStack;

    unsigned int firstIndex = firstString.size();
    unsigned int secondIndex = secondString.size();

    while (true)
    {
        if (firstString[firstIndex - 1] == secondString[secondIndex - 1])
        {
            lcsStack.push(firstString[firstIndex - 1]);

            --firstIndex;
            --secondIndex;
        }
        else
        {
            if (lcsLengths[firstIndex - 1][secondIndex] > lcsLengths[firstIndex][secondIndex - 1])
            {
                --firstIndex;
            }
            else
            {
                --secondIndex;
            }
        }

        if (firstIndex <= 0 || secondIndex <= 0)
        {
            break;
        }
    }

    std::string lcs;
    while (lcsStack.empty() == false)
    {
        lcs.push_back(lcsStack.top());
        lcsStack.pop();
    }

    std::cout << lcsLengths[firstString.size()][secondString.size()] << std::endl;
    std::cout << lcs;

    return 0;
}