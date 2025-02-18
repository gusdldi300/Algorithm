
#include <iostream>
#include <stack>
#include <string>

int main()
{
    std::string compressedString;
    std::cin >> compressedString;

    unsigned int decompressedCount = 0;
    bool bRepeat = false;

    std::stack<char> charStack;
    for (std::string::const_reverse_iterator constReverseIter = compressedString.rbegin(); constReverseIter != compressedString.rend(); ++constReverseIter)
    {
        char character = *constReverseIter;
        
        if (bRepeat)
        {
            unsigned int repeatCount = character - '0';
            decompressedCount *= repeatCount;

            bRepeat = false;

            continue;
        }

        if (character == '(') 
        {
            while (charStack.empty() == false) 
            {
                char popCharacter = charStack.top();
                charStack.pop();

                if (popCharacter == ')')
                {
                    bRepeat = true;
                    break;
                }

                ++decompressedCount;
            }

            if (bRepeat)
            {
                continue;
            }
        }

        charStack.push(character);
    }

    decompressedCount += charStack.size();
    std::cout << decompressedCount;

    return 0;
}