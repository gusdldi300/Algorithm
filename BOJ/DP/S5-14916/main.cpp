
#include <iostream>
#include <climits>

#define MAX_CHANGE_AMOUNT (100000U)

int main()
{
    int cache[MAX_CHANGE_AMOUNT + 1] = { 0, };
    cache[1] = INT_MAX;
    cache[2] = 1;
    cache[3] = INT_MAX;
    cache[4] = 2;
    cache[5] = 1;

    int changeAmount = 0;
    std::cin >> changeAmount;
    
    for (unsigned int i = 6; i <= changeAmount; ++i)
    {
        int first = cache[i - 2];
        int second = cache[i - 5];
        
        if (first == INT_MAX && second == INT_MAX)
        {
            cache[i] = INT_MAX;
            continue;
        }

        cache[i] = (first < second ? first : second) + 1;
    }

    std::cout << (cache[changeAmount] == INT_MAX ? -1 : cache[changeAmount]);

    return 0;
}