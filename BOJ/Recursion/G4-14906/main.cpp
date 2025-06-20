
#include <iostream>
#include <string>

#define MAX_STRINGS_COUNT (10)
#define MAX_STRING_SIZE (60)

/*
 * bool: Result
 * int: Read string count
 */
std::pair<bool, int> IsSlumpRecursive(const char* testString)
{
    const char* checkString = testString;
    if ((*checkString != 'D' && *checkString != 'E') || *checkString == '\0')
    {
        return std::pair<bool, int>(false, 0);
    }

    int fCount = 0;
    while (*(++checkString) == 'F')
    {
        ++fCount;
    }

    if (fCount == 0)
    {
        return std::pair<bool, int>(false, 0);
    }

    if (*checkString == 'G')
    {
        return std::pair<bool, int>(true, 2 + fCount);
    }
    else
    {
        std::pair<bool, int> result = IsSlumpRecursive(checkString);
        if (result.first)
        {
            return std::pair<bool, int>(true, 1 + fCount + result.second);
        }
    }

    return std::pair<bool, int>(false, 0);
}

std::pair<bool, int> IsSlimpRecursive(const char* testString)
{
    const char* checkString = testString;
    if (*checkString != 'A' || *checkString == '\0')
    {
        return std::pair<bool, int>(false, 0);
    }

    ++checkString;
    if (*checkString == 'H')
    {
        return std::pair<bool, int>(true, 2);
    }
    
    if (*checkString == 'B')
    {
        ++checkString;
        std::pair<bool, int> slimpResult = IsSlimpRecursive(checkString);
        if (slimpResult.first == false)
        {
            return std::pair<bool, int>(false, 0);
        }

        checkString += slimpResult.second;
        if (*checkString == 'C')
        {
            return std::pair<bool, int>(true, slimpResult.second + 3);
        }
    }
    else
    {
        std::pair<bool, int> slumpResult = IsSlumpRecursive(checkString);
        if (slumpResult.first == false)
        {
            return std::pair<bool, int>(false, 0);
        }

        checkString += slumpResult.second;
        if (*checkString == 'C')
        {
            return std::pair<bool, int>(true, slumpResult.second + 2);
        }
    }
    
    return std::pair<bool, int>(false, 0);
}

int main()
{
    int testCount = 0;
    std::cin >> testCount;
    
    std::string testStrings[MAX_STRINGS_COUNT];
    for (int i = 0; i < testCount; ++i)
    {
        std::cin >> testStrings[i];
    }

    std::cout << "SLURPYS OUTPUT" << std::endl;
    for (int i = 0; i < testCount; ++i)
    {
        std::pair<bool, int> slimpResult;
        slimpResult.first = false;
        slimpResult.second = 0;

        std::pair<bool, int> slumpResult;
        slumpResult.first = false;
        slumpResult.second = 0;

        const char* checkString = testStrings[i].c_str();
        slimpResult = IsSlimpRecursive(checkString);
        if (slimpResult.first)
        {
            checkString += slimpResult.second;
            slumpResult = IsSlumpRecursive(checkString);
            if (slumpResult.first && *(checkString + slumpResult.second) == '\0')
            {
                std::cout << "YES" << std::endl;

                continue;
            }
        }

        std::cout << "NO" << std::endl;
    }

    std::cout << "END OF OUTPUT" << std::endl;

    return 0;
}