
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int main()
{
    unsigned int ballsCount;
    std::cin >> ballsCount;

    std::vector<unsigned int> balls;
    for (unsigned int i = 0; i < ballsCount; ++i)
    {
        int ball;
        std::cin >> ball;

        balls.push_back(ball);
    }

    std::sort(balls.begin(), balls.end());

    unsigned int firstTopIndex = 0;
    unsigned int firstUnderIndex = ballsCount - 1;

    int minHeightDifference = INT_MAX;

    for (unsigned int firstTopIndex = 0; firstTopIndex < ballsCount; ++firstTopIndex)
    {
        for (unsigned int firstUnderIndex = firstTopIndex + 1; firstUnderIndex < ballsCount; ++firstUnderIndex)
        {
            int firstHeight = balls[firstTopIndex] + balls[firstUnderIndex];

            unsigned int secondTopIndex = firstTopIndex + 1;
            unsigned int secondUnderIndex = firstUnderIndex - 1;

            while (secondTopIndex < secondUnderIndex)
            {
                int secondHeight = balls[secondTopIndex] + balls[secondUnderIndex];
                minHeightDifference = std::min(minHeightDifference, std::abs(firstHeight - secondHeight));

                if (secondHeight > firstHeight)
                {
                    --secondUnderIndex;
                }
                else
                {
                    ++secondTopIndex;
                }
            }
        }
    }

    std::cout << minHeightDifference;

    return 0;
}