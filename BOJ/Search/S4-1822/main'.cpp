
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned int aSetCount;
    unsigned int bSetCount;

    std::cin >> aSetCount >> bSetCount;

    std::vector<unsigned int> aSetAscend;
    for (unsigned int i = 0; i < aSetCount; ++i)
    {
        unsigned int number;
        std::cin >> number;

        aSetAscend.push_back(number);
    }

    std::vector<unsigned int> bSetAscend;
    for (unsigned int i = 0; i < bSetCount; ++i)
    {
        unsigned int number;
        std::cin >> number;
        
        bSetAscend.push_back(number);
    }

    std::sort(aSetAscend.begin(), aSetAscend.end());
    std::sort(bSetAscend.begin(), bSetAscend.end());

    std::vector<unsigned int> nonEqualASetAscend;
    for (unsigned int number : aSetAscend)
    {
        if (std::binary_search(bSetAscend.begin(), bSetAscend.end(), number) == false)
        {
            nonEqualASetAscend.push_back(number);
        }
    }

    std::cout << nonEqualASetAscend.size() << '\n';
    for (unsigned int number : nonEqualASetAscend)
    {
        std::cout << number << ' ';
    }

    return 0;
}