
#include <iostream>
#include <vector>
#include <algorithm>

struct StringChar
{
    char Character;
    int Index;
};

bool CompareStringCharByIndex(const StringChar& first, const StringChar& second)
{
    return first.Index < second.Index;
}

static void PrintString(const std::vector<StringChar>& stringChars)
{
    std::string printString;
    printString.reserve(stringChars.size());

    for (const StringChar& stringChar : stringChars)
    {
        printString.push_back(stringChar.Character);
    }
    
    std::cout << printString << std::endl;
}

static void PrintStringRecursive(int startIndex, int endIndex, const std::string& string, std::vector<StringChar>* outPrintStringChars)
{
    if (startIndex > endIndex)
    {
        return;
    }

    StringChar minStringChar;
    minStringChar.Character = string[startIndex];
    minStringChar.Index = startIndex;

    for (int i = startIndex + 1; i <= endIndex; ++i)
    {
        if (string[i] < minStringChar.Character)
        {
            minStringChar.Character = string[i];
            minStringChar.Index = i;
        }
    }

    outPrintStringChars->push_back(minStringChar);
    std::stable_sort(outPrintStringChars->begin(), outPrintStringChars->end(), CompareStringCharByIndex);
    PrintString(*outPrintStringChars);

    PrintStringRecursive(minStringChar.Index + 1, endIndex, string, outPrintStringChars);
    PrintStringRecursive(startIndex, minStringChar.Index - 1, string, outPrintStringChars);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string string;
    std::cin >> string;

    std::vector<StringChar> printStringChars;
    printStringChars.reserve(string.size() + 1);

    PrintStringRecursive(0, string.size() - 1, string, &printStringChars);

    return 0;
}