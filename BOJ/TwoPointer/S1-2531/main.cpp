#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

int main()
{
    unsigned int dishesCount;
    unsigned int typesCount;
    unsigned int continuosDishesCount;
    unsigned int couponType;
    
    std::cin >> dishesCount >> typesCount >> continuosDishesCount >> couponType;
    
    std::vector<unsigned int> dishes;
    for (unsigned int i = 0; i < dishesCount; ++i)
    {
        unsigned int type;
        std::cin >> type;
            
        dishes.push_back(type);
    }

    for (unsigned int i = 0; i < continuosDishesCount - 1; ++i)
    {
        dishes.push_back(dishes[i]);
    }

    unsigned int maxTypesCount = 0;
    unsigned int ateCount = 0;
    std::unordered_map<unsigned int, unsigned int> dishTypeAteCounts;
    
    unsigned int startIndex = 0;
    for (unsigned int endIndex = 0; endIndex < dishes.size(); ++endIndex)
    {
        dishTypeAteCounts[dishes[endIndex]]++;
        ateCount++;
        
        if (ateCount >= continuosDishesCount)
        {
            if (dishTypeAteCounts.find(couponType) == dishTypeAteCounts.end())
            {
                maxTypesCount = std::max(maxTypesCount, static_cast<unsigned int>(dishTypeAteCounts.size()) + 1);
            }
            else
            {
                maxTypesCount = std::max(maxTypesCount, static_cast<unsigned int>(dishTypeAteCounts.size()));
            }

            assert(dishTypeAteCounts.find(dishes[startIndex]) != dishTypeAteCounts.end());
            dishTypeAteCounts[dishes[startIndex]]--;

            if (dishTypeAteCounts[dishes[startIndex]] == 0)
            {
                dishTypeAteCounts.erase(dishes[startIndex]);
            }

            ateCount--;
            startIndex++;
        }
    }

    std::cout << maxTypesCount;

    return 0;
}