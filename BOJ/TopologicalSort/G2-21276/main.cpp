
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int peopleCount;
    std::cin >> peopleCount;

    std::map<std::string, std::set<std::string>> peopleLineageMapAscend;

    std::unordered_map<std::string, std::vector<std::string>> parentChildrenMap;
    std::unordered_map<std::string, unsigned int> personParentCountMap;

    for (unsigned int i = 0; i < peopleCount; ++i)
    {
        std::string person;
        std::cin >> person;

        peopleLineageMapAscend.insert(std::pair<std::string, std::set<std::string>>(person, std::set<std::string>()));

        parentChildrenMap.insert(std::pair<std::string, std::vector<std::string>>(person, std::vector<std::string>()));
        personParentCountMap.insert(std::pair<std::string, unsigned int>(person, 0));
    }

    unsigned int relationsCount;
    std::cin >> relationsCount;

    for (unsigned int i = 0; i < relationsCount; ++i)
    {
        std::string parent;
        std::string child;

        std::cin >> child >> parent;

        parentChildrenMap[parent].push_back(child);
        ++personParentCountMap[child];
    }

    std::vector<std::string> rootParentsAscend;

    std::queue<std::string> parentQueue;
    for (const std::pair<std::string, unsigned int>& personParentsCountPair : personParentCountMap)
    {
        if (personParentsCountPair.second == 0)
        {
            parentQueue.push(personParentsCountPair.first);
            rootParentsAscend.push_back(personParentsCountPair.first);
        }
    }

    std::sort(rootParentsAscend.begin(), rootParentsAscend.end());

    std::cout << rootParentsAscend.size() << '\n';
    for (const std::string& rootParent : rootParentsAscend)
    {
        std::cout << rootParent << ' ';
    }
    std::cout << '\n';

    while (parentQueue.empty() == false)
    {
        std::string parent = parentQueue.front();
        parentQueue.pop();

        const std::vector<std::string>& children = parentChildrenMap[parent];
        for (const std::string& child : children)
        {
            --personParentCountMap[child];

            if (personParentCountMap[child] == 0)
            {
                peopleLineageMapAscend[parent].insert(child);

                parentQueue.push(child);
            }
        }
    }

    for (const std::pair<std::string, std::set<std::string>>& personChildrenPair : peopleLineageMapAscend)
    {
        std::cout << personChildrenPair.first << ' ' << personChildrenPair.second.size() << ' ';
        
        for (const std::string& child : personChildrenPair.second)
        {
            std::cout << child << ' ';
        }

        std::cout << '\n';
    }

    return 0;
}