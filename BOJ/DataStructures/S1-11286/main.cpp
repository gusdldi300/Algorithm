
#include <iostream>
#include <queue>

struct Comparator
{
    bool operator()(const int first, int second) const
    {
        int absFirst = std::abs(first);
        int absSecond = std::abs(second);

        if (absFirst == absSecond)
        {
            return first > second;
        }

        return absFirst > absSecond;
    }
};

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int operationsCount;
    std::cin >> operationsCount;

    std::priority_queue<int, std::vector<int>, Comparator> numberQueueAbsAscend;
    for (unsigned int i = 0; i < operationsCount; ++i)
    {
        int operation;
        std::cin >> operation;

        if (operation == 0)
        {
            if (numberQueueAbsAscend.empty())
            {
                std::cout << 0 << '\n';

                continue;
            }

            int minAbsNumber = numberQueueAbsAscend.top();
            numberQueueAbsAscend.pop();

            std::cout << minAbsNumber << '\n';

            continue;
        }

        numberQueueAbsAscend.push(operation);
    }

    return 0;
}