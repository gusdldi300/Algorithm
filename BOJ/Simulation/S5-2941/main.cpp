
#include <iostream>
#include <string>

#define MAX_WORD_SIZE (101U)

int main()
{
    std::string word;
    word.reserve(MAX_WORD_SIZE);
    std::cin >> word;

    std::string transformedWord;
    transformedWord.reserve(MAX_WORD_SIZE);

    size_t searchIndex = 0;
    while (searchIndex < word.size())
    {
        char checkChar = word[searchIndex];

        if (searchIndex == (word.size() - 1))
        {
            transformedWord.push_back(checkChar);

            break;
        }
        
        bool bCroaticChar = false;
        switch (checkChar)
        {
        case 'c':
            if (word[searchIndex + 1] == '=' || word[searchIndex + 1] == '-')
            {
                bCroaticChar = true;
            }

            break;

        case 'd':
            if (word[searchIndex + 1] == '-')
            {
                bCroaticChar = true;
            }
            else if (searchIndex < (word.size() - 2) && word[searchIndex + 1] == 'z' && word[searchIndex + 2] == '=')
            {
                bCroaticChar = true;

                searchIndex++;
            }

            break;
            
        case 'l':
            // Intentional fallthrough
        case 'n':

            if (word[searchIndex + 1] == 'j')
            {
                bCroaticChar = true;
            }

            break;

        case 's':
            // Intentional fallthrough

        case 'z':
            if (word[searchIndex + 1] == '=')
            {
                bCroaticChar = true;
            }

            break;
        }

        if (bCroaticChar)
        {
            transformedWord.push_back('1');

            searchIndex++;
        }
        else
        {
            transformedWord.push_back(checkChar);
        }

        searchIndex++;
    }

    std::cout << transformedWord.size();

    return 0;
}