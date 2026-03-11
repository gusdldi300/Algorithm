
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int groupsCount;
    unsigned int problemsCount;

    std::cin >> groupsCount >> problemsCount;
    
    std::unordered_map<std::string, std::set<std::string>> groupMembersAscendMap;
    for (unsigned int i = 0; i < groupsCount; ++i)
    {
        std::string group;
        std::cin >> group;

        unsigned int membersCount;
        std::cin >> membersCount;

        groupMembersAscendMap.insert(std::pair<std::string, std::set<std::string>>(group, std::set<std::string>()));
        for (unsigned int j = 0; j < membersCount; ++j)
        {
            std::string member;
            std::cin >> member;

            groupMembersAscendMap[group].insert(member);
        }
    }

    for (unsigned int i = 0; i < problemsCount; ++i)
    {
        std::string name;
        unsigned int problem;
        
        std::cin >> name >> problem;
        if (problem == 0)
        {
            const std::set<std::string>& membersAscend = groupMembersAscendMap[name];
            for (const std::string& member : membersAscend)
            {
                std::cout << member << '\n';
            }
        }
        else
        {
            for (const auto& groupMember : groupMembersAscendMap)
            {
                if (groupMember.second.find(name) != groupMember.second.end())
                {
                    std::cout << groupMember.first << '\n';

                    break;
                }
            }
        }
    }

    return 0;
}