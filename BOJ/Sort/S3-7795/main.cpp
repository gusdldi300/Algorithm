
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int i = 0; i < testsCount; ++i)
    {
        unsigned int aCounts;
        unsigned int bCounts;

        std::cin >> aCounts >> bCounts;

        std::vector<unsigned int> aCreatures;

        for (unsigned int j = 0; j < aCounts; ++j)
        {
            unsigned int a;
            std::cin >> a;
            aCreatures.push_back(a);
        }

        std::vector<unsigned int> bCreatures;

        for (unsigned int j = 0; j < bCounts; ++j)
        {
            unsigned int b;
            std::cin >> b;
            bCreatures.push_back(b);
        }

        std::sort(aCreatures.begin(), aCreatures.end());
        std::sort(bCreatures.begin(), bCreatures.end());

        unsigned int aBiggerCount = 0;
        for (unsigned int a : aCreatures)
        {
            for (unsigned int b : bCreatures)
            {
                if (a <= b)
                {
                    break;
                }

                ++aBiggerCount;
            }
        }

        std::cout << aBiggerCount << std::endl;
    }

    return 0;
}
