#include <climits>
#include <iostream>
#include <queue>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int operationsCount;
    std::cin >> operationsCount;

    std::priority_queue<unsigned int> numbersDescend;
    for (unsigned int i = 0; i < operationsCount; ++i)
    {
        unsigned int operation;
        std::cin >> operation;

        if (operation > 0)
        {
            numbersDescend.push(operation);

            continue;
        }

        unsigned int outNumber = UINT_MAX;
        if (numbersDescend.empty())
        {
            outNumber = 0;
        }
        else
        {
            outNumber = numbersDescend.top();
            numbersDescend.pop();
        }

        std::cout << outNumber << '\n';
    }

    return 0;
}