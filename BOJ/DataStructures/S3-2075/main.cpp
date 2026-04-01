
#include <iostream>
#include <queue>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int gridSize;
    std::cin >> gridSize;

    std::priority_queue<int, std::vector<int>, std::greater<int>> numberQueueAscend;
    for (unsigned int row = 0; row < gridSize; ++row)
    {
        for (unsigned int col = 0; col < gridSize; ++col)
        {
            int number;
            std::cin >> number;

            numberQueueAscend.push(number);

            if (numberQueueAscend.size() > gridSize)
            {
                numberQueueAscend.pop();
            }
        }
    }

    std::cout << numberQueueAscend.top();

    return 0;
}