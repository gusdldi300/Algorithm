#include <iostream>
#include <queue>

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
    
    if (numbersCount == 1)
    {
        return 0;
    }

    std::cin >> number;
    midLeftEqualNumbersDescend.push(number);
    midRightNumbersAscend.push(midLeftEqualNumbersDescend.top());

    midLeftEqualNumbersDescend.pop();

    std::cout << midLeftEqualNumbersDescend.top() << '\n';

    for (unsigned int i = 2; i < numbersCount; ++i)
    {
        std::cin >> number;

        if (midLeftEqualNumbersDescend.size() <= midRightNumbersAscend.size())
        {
            midLeftEqualNumbersDescend.push(number);
        }
        else
        {
            midRightNumbersAscend.push(number);
        }

        if (midLeftEqualNumbersDescend.top() > midRightNumbersAscend.top())
        {
            int leftNumber = midLeftEqualNumbersDescend.top();
            midLeftEqualNumbersDescend.pop();

            int rightNumber = midRightNumbersAscend.top();
            midRightNumbersAscend.pop();

            midLeftEqualNumbersDescend.push(rightNumber);
            midRightNumbersAscend.push(leftNumber);
        }

        std::cout << midLeftEqualNumbersDescend.top() << '\n';
    }

    return 0;
}