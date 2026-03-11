
#include <string>
#include <iostream>
#include <unordered_set>

int main()
{
    std::string string;
    std::cin >> string;

    std::unordered_set<std::string> uniqueSubStrings;
    for (unsigned int subStringSize = 1; subStringSize <= string.size(); ++subStringSize)
    {
        for (unsigned int startIndex = 0; startIndex <= (string.size() - subStringSize); ++startIndex)
        {
            std::string subString;
            subString.reserve(string.size());

            for (unsigned int count = 0; count < subStringSize; ++count)
            {
                subString.push_back(string[startIndex + count]);
            }

            uniqueSubStrings.insert(subString);
        }
    }

    std::cout << uniqueSubStrings.size();

    return 0;
}