
#include <iostream>
#include <stack>
#include <string>

unsigned int GetDecompressedCountRecursive(std::string& compressedString, int& stringIndex, std::stack<char>& characterStack, unsigned int decompressedCount);

int main()
{
    std::string compressedString;
    std::cin >> compressedString;

    unsigned int totalDecompressedCount = 0;
    unsigned int decompressedCount = 0;

    int stringIndex = compressedString.size() - 1;
    std::stack<char> characterStack;
    while (stringIndex >= 0)
    {
        char character = compressedString[stringIndex];
        --stringIndex;

        characterStack.push(character);

        if (character == ')')
        {
            totalDecompressedCount += GetDecompressedCountRecursive(compressedString, stringIndex, characterStack, 0);
        }
    }

    totalDecompressedCount += (unsigned int)characterStack.size();
    std::cout << totalDecompressedCount;

    return 0;
}

unsigned int GetDecompressedCountRecursive(std::string& compressedString, int& stringIndex, std::stack<char>& characterStack, unsigned int decompressedCount)
{
    while (stringIndex >= 0)
    {
        char character = compressedString[stringIndex];
        --stringIndex;
        
        characterStack.push(character);
        
        if (character == ')')
        {
            decompressedCount += GetDecompressedCountRecursive(compressedString, stringIndex, characterStack, 0);

            continue;
        }

        if (character == '(')
        {
            characterStack.pop();

            unsigned int repeatCount = compressedString[stringIndex] - '0';
            --stringIndex;
            
            while (true)
            {
                char checkBracket = characterStack.top();
                characterStack.pop();
                if (checkBracket == ')') 
                {
                    break;
                }

                decompressedCount++;
            }
            
            return decompressedCount * repeatCount;
        }
    }

    return decompressedCount;
}