#include <iostream>
#include <queue>
#include <climits>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int numbersCount;
    std::cin >> numbersCount;

    std::priority_queue<int> midLeftEqualNumbersDescend;
    std::priority_queue<int, std::vector<int>, std::greater<int>> midRightNumbersAscend;

    int number;
    std::cin >> number;

    midLeftEqualNumbersDescend.push(number);
    std::cout << number << '\n';

    for (unsigned int i = 1; i < numbersCount; ++i)
    {
        int number;
        std::cin >> number;

        midLeftEqualNumbersDescend.push(number);

        int midNumber = INT_MAX;
        if (midLeftEqualNumbersDescend.size() > midRightNumbersAscend.size() + 1)
        {
            midRightNumbersAscend.push(midLeftEqualNumbersDescend.top());
            midLeftEqualNumbersDescend.pop();

            midNumber = std::min(midLeftEqualNumbersDescend.top(), midRightNumbersAscend.top());
        }
        else
        {
            if (midLeftEqualNumbersDescend.top() > midRightNumbersAscend.top())
            {
                int leftNumber = midLeftEqualNumbersDescend.top();
                midLeftEqualNumbersDescend.pop();

                int rightNumber = midRightNumbersAscend.top();
                midRightNumbersAscend.pop();

                midLeftEqualNumbersDescend.push(rightNumber);
                midRightNumbersAscend.push(leftNumber);
            }

            midNumber = midLeftEqualNumbersDescend.top();
        }

        std::cout << midNumber << '\n';
    }

    return 0;
}