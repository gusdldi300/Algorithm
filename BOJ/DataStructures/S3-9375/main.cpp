
#include <iostream>
#include <unordered_map>

static unsigned int GetWearCountRecursive(unsigned int wearTypesCount, unsigned int typeIndex, const std::vector<std::string>& wearTypes, std::unordered_map<std::string, std::vector<std::string>>& wearTypeAndNamesMap)
{
    if (wearTypesCount == 0)
    {
        return 1;
    }

    if (typeIndex == wearTypes.size())
    {
        return 0;
    }

    unsigned int totalCount = 0;
    for (unsigned int i = typeIndex; i < wearTypes.size(); ++i)
    {
        unsigned int count = wearTypeAndNamesMap[wearTypes[i]].size();
        count *= GetWearCountRecursive(wearTypesCount - 1, i + 1, wearTypes, wearTypeAndNamesMap);

        totalCount += count;
    }

    return totalCount;
}


int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int testsCount;
    std::cin >> testsCount;
        
    for (unsigned int test = 0; test < testsCount; ++test)
    {
        unsigned int wearsCount;
        std::cin >> wearsCount;

        std::unordered_map<std::string, std::vector<std::string>> wearTypeAndNamesMap;
        for (unsigned int i = 0; i < wearsCount; ++i)
        {
            std::string name;
            std::string type;

            std::cin >> name >> type;
            
            if (wearTypeAndNamesMap.find(type) == wearTypeAndNamesMap.end())
            {
                wearTypeAndNamesMap.insert(std::pair<std::string, std::vector<std::string>>(type, std::vector<std::string>()));
            }

            wearTypeAndNamesMap[type].push_back(name);
        }

        std::vector<std::string> wearTypes;
        for (auto iter = wearTypeAndNamesMap.begin(); iter != wearTypeAndNamesMap.end(); ++iter)
        {
            wearTypes.push_back(iter->first);
        }

        unsigned int totalCount = 0;
        for (unsigned int wearTypesCount = 1; wearTypesCount <= wearTypeAndNamesMap.size(); ++wearTypesCount)
        {
            totalCount += GetWearCountRecursive(wearTypesCount, 0, wearTypes, wearTypeAndNamesMap);
        }

        std::cout << totalCount << '\n';
    }

    return 0;
}