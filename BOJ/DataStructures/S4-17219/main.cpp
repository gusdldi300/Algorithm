
#include <iostream>
#include <unordered_map>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int sitesCount;
    unsigned int findSitesCount;
    
    std::cin >> sitesCount >> findSitesCount;
    
    std::unordered_map<std::string, std::string> sitePasswordMap;
    for (unsigned int i = 0; i < sitesCount; ++i)
    {
        std::string site;
        std::string password;
        
        std::cin >> site >> password;

        sitePasswordMap.insert(std::pair<std::string, std::string>(site, password));
    }

    for (unsigned int i = 0; i < findSitesCount; ++i)
    {
        std::string site;
        std::cin >> site;

        std::cout << sitePasswordMap[site] << '\n';
    }

    return 0;
}