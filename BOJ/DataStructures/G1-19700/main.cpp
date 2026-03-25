#include <iostream>
#include <map>
#include <cassert>

int main()
{
    unsigned int studentsCount;
    std::cin >> studentsCount;

    std::map<unsigned int, unsigned int> heightAndMaxTallerCountMapAscend;
    for (unsigned int i = 0; i < studentsCount; ++i)
    {
        unsigned int height;
        unsigned int maxTallerCount;
        std::cin >> height >> maxTallerCount;
        
        heightAndMaxTallerCountMapAscend.insert(std::pair<unsigned int, unsigned int>(height, maxTallerCount));
    }
    
    std::map<unsigned int, unsigned int> tallerGroupSizeAndCountMapAscend;

    for (auto rIter = heightAndMaxTallerCountMapAscend.rbegin(); rIter != heightAndMaxTallerCountMapAscend.rend(); ++rIter)
    {
        auto tallerGroupSizeAndCountIter = tallerGroupSizeAndCountMapAscend.lower_bound(rIter->second);
        if (tallerGroupSizeAndCountIter == tallerGroupSizeAndCountMapAscend.begin())
        {
            ++tallerGroupSizeAndCountMapAscend[1];

            continue;
        }

        --tallerGroupSizeAndCountIter;

        unsigned int tallerGroupSize = tallerGroupSizeAndCountIter->first;
        ++tallerGroupSizeAndCountMapAscend[tallerGroupSize + 1];
        --tallerGroupSizeAndCountMapAscend[tallerGroupSize];

        if (tallerGroupSizeAndCountMapAscend[tallerGroupSize] == 0)
        {
            tallerGroupSizeAndCountMapAscend.erase(tallerGroupSize);
        }
    }

    unsigned int minGroupCount = 0;
    for (const auto& tallerGroupSizeAndCountIter : tallerGroupSizeAndCountMapAscend)
    {
        minGroupCount += tallerGroupSizeAndCountIter.second;
    }

    std::cout << minGroupCount;

    return 0;
}