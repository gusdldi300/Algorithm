
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string string;
    std::cin >> string;

    std::vector<std::string> subStringsAscend;
    for (unsigned int i = 0; i < string.size(); ++i)
    {
        std::string subString = string.substr(i);
        
        subStringsAscend.push_back(subString);
    }

    std::sort(subStringsAscend.begin(), subStringsAscend.end());
    for (const std::string& subString : subStringsAscend)
    {
        std::cout << subString << std::endl;
    }

    return 0;
}