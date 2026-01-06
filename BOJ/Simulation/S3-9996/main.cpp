
#include <iostream>
#include <string>

#define MAX_FILE_SIZE (101U)

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int filesCount;
    std::cin >> filesCount;

    std::string pattern;
    pattern.reserve(MAX_FILE_SIZE);
    
    std::cin >> pattern;

    std::string leftString;
    leftString.reserve(MAX_FILE_SIZE);

    std::string reversedRightString;
    leftString.reserve(MAX_FILE_SIZE);

    for (int patternIndex = 0; patternIndex < pattern.size(); ++patternIndex)
    {
        if (pattern[patternIndex] == '*')
        {
            break;
        }

        leftString.push_back(pattern[patternIndex]);
    }

    for (int patternIndex = pattern.size() - 1; patternIndex >= 0; --patternIndex)
    {
        if (pattern[patternIndex] == '*')
        {
            break;
        }

        reversedRightString.push_back(pattern[patternIndex]);
    }

    for (unsigned int i = 0; i < filesCount; ++i)
    {
        std::string file;
        file.reserve(MAX_FILE_SIZE);
    
        std::cin >> file;

        std::string reversedFile;
        file.reserve(MAX_FILE_SIZE);

        for (int i = file.size() - 1; i >= 0; --i)
        {
            reversedFile.push_back(file[i]);
        }

        if (file.find(leftString) == 0 && 
            reversedFile.find(reversedRightString) == 0 && 
            (file.size() >= pattern.size() - 1))
        {
            std::cout << "DA" << std::endl;
        }
        else
        {
            std::cout << "NE" << std::endl;
        }
    }

    return 0;
}