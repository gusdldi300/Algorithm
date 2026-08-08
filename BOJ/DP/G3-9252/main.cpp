
#include <algorithm>
#include <iostream>
#include <stack>

#define MAX_STRING_SIZE (1001U)

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string firstString;
    std::string secondString;

    std::cin >> firstString >> secondString;

    unsigned int lcsCounts[MAX_STRING_SIZE][MAX_STRING_SIZE] = { 0, };
    for (unsigned int firstIndex = 0; firstIndex < firstString.size(); ++firstIndex)
    {
        for (unsigned int secondIndex = 0; secondIndex < secondString.size(); ++secondIndex)
        {
            if (firstString[firstIndex] == secondString[secondIndex])
            {
                lcsCounts[firstIndex + 1][secondIndex + 1] = lcsCounts[firstIndex][secondIndex] + 1;

                continue;
            }

            lcsCounts[firstIndex + 1][secondIndex + 1] = std::max(lcsCounts[firstIndex][secondIndex + 1], lcsCounts[firstIndex + 1][secondIndex]);
        }
    }

    std::stack<char> lcsStack;
    int firstIndex = firstString.size() - 1;
    int secondIndex = secondString.size() - 1;
    
    while (true)
    {
        if (firstIndex < 0 || secondIndex < 0)
        {
            break;
        }

        if (firstString[firstIndex] == secondString[secondIndex])
        {
            lcsStack.push(firstString[firstIndex]);

            firstIndex--;
            secondIndex--;

            continue;
        }

        if (lcsCounts[firstIndex + 1][secondIndex] >= lcsCounts[firstIndex][secondIndex + 1])
        {
            secondIndex--;
        }
        else
        {
            firstIndex--;
        }
    }

    std::cout << lcsStack.size() << '\n';

    if (lcsStack.empty())
    {
        return 0;
    }

    std::string lcsString;
    lcsString.reserve(lcsStack.size() + 1);

    while (lcsStack.empty() == false)
    {
        lcsString.push_back(lcsStack.top());

        lcsStack.pop();
    }

    std::cout << lcsString;

    return 0;
}