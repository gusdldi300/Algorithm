
#include <iostream>
#include <string>
#include <cassert>

#define MAX_VALUE_NAME_SIZE (101U)
#define TRANSFORM_ALPHABET_OFFSET (32U)

#define UNDER_BAR_CHAR '_'


bool IsUpperCase(char alphabet)
{
    if (alphabet >= 'A' && alphabet <= 'Z')
    {
        return true;
    }

    return false;
}

int main()
{
    std::string valueName;
    valueName.reserve(MAX_VALUE_NAME_SIZE);
    std::cin >> valueName;

    assert(valueName.size() > 0);

    bool bCpp = false;
    bool bJava = false;

    std::string transformedName;
    transformedName.reserve(MAX_VALUE_NAME_SIZE);

    if (IsUpperCase(valueName[0]) ||
        valueName[0] == UNDER_BAR_CHAR || valueName[valueName.size() - 1] == UNDER_BAR_CHAR)
    {
        goto ERROR_LABEL;
    }

    for (unsigned int i = 1; i < valueName.size(); ++i)
    {
        char checkChar = valueName[i];

        if (IsUpperCase(checkChar))
        { 
            bJava = true;
        }
        else if (checkChar == UNDER_BAR_CHAR)
        {
            bCpp = true;
        }

        if (valueName[i] == UNDER_BAR_CHAR && valueName[i - 1] == UNDER_BAR_CHAR)
        {
            goto ERROR_LABEL;
        }
    }

    if (bJava && bCpp)
    {
        goto ERROR_LABEL;
    }

    // Transform value name
    if (bJava)
    {
        for (unsigned int i = 0; i < valueName.size(); ++i)
        {
            char addChar = valueName[i];

            if (IsUpperCase(addChar))
            {
                transformedName.push_back(UNDER_BAR_CHAR);

                addChar += TRANSFORM_ALPHABET_OFFSET;
            }

            transformedName.push_back(addChar);
        }
    }
    else
    {
        bool bToUpper = false;
        for (unsigned int i = 0; i < valueName.size(); ++i)
        {
            char addChar = valueName[i];

            if (addChar == UNDER_BAR_CHAR)
            {
                bToUpper = true;

                continue;
            }

            if (bToUpper)
            {
                bToUpper = false;
                
                addChar -= TRANSFORM_ALPHABET_OFFSET;
            }

            transformedName.push_back(addChar);
        }
    }

    std::cout << transformedName;

    return 0;

ERROR_LABEL:
    std::cout << "Error!";

    return 0;
}