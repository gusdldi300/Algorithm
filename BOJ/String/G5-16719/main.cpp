
#include <iostream>
#include <vector>
#include <algorithm>

struct StringChar
{
    char Character;
    unsigned int Index;
};

bool CompareStringCharByCharacter(const StringChar& first, const StringChar& second)
{
    return first.Character < second.Character;
}

bool CompareStringCharByIndex(const StringChar& first, const StringChar& second)
{
    return first.Index < second.Index;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string string;
    std::cin >> string;

    std::vector<StringChar> stringCharsCharacterAscend;
    for (unsigned int i = 0; i < string.size(); ++i)
    {
        StringChar stringChar;
        stringChar.Character = string[i];
        stringChar.Index = i;

        stringCharsCharacterAscend.push_back(std::move(stringChar));
    }

    std::stable_sort(stringCharsCharacterAscend.begin(), stringCharsCharacterAscend.end(), CompareStringCharByCharacter);
    
    std::vector<StringChar> printStringChar;
    printStringChar.reserve(string.size() + 1);

    std::string printString;
    printString.reserve(string.size() + 1);
    for (StringChar stringChar : stringCharsCharacterAscend)
    {
        printStringChar.push_back(std::move(stringChar));
        std::stable_sort(printStringChar.begin(), printStringChar.end(), CompareStringCharByIndex);
        
        for (StringChar printStringChar : printStringChar)
        {
            printString.push_back(printStringChar.Character);
        }

        std::cout << printString << '\n';
        printString.clear();
    }

    return 0;
}