
#include <iostream>
#include <string>
#include <cassert>

#define MAX_PASSWORD_SIZE (5001U)
#define MAX_ALPHABET_INDEX (26U)
#define ONE_DIGIT_INDEX (0U)
#define TWO_DIGIT_INDEX (1U)

#define CASE_DIVISOR (1000000U)

static unsigned int sCases[2][MAX_PASSWORD_SIZE] = { 0, };

static bool IsLastTwoDigitAlphabet(const std::string& password, unsigned int passwordIndex)
{
    char alphabet = (password[passwordIndex - 1] - '0') * 10;
    alphabet += (password[passwordIndex] - '0');
    
    if (alphabet < 10 || alphabet > MAX_ALPHABET_INDEX)
    {
        return false;
    }

    return true;
}

static bool IsCorrectPassword(const std::string& password, unsigned int passwordIndex)
{
    assert(passwordIndex > 0);

    if (password[passwordIndex] != '0')
    {
        return true;
    }

    if (password[passwordIndex - 1] == '1' || password[passwordIndex - 1] == '2')
    {
        return true;
    }

    return false;
}

int main()
{
    std::string password;
    std::cin >> password;

    if (password[0] == '0')
    {
        goto WRONG_PASSWORD_LABEL;
    }

    if (password.size() == 1)
    {
        std::cout << 1;

        return 0;
    }

    sCases[ONE_DIGIT_INDEX][0] = 1;

    if (IsCorrectPassword(password, 1) == false)
    {
        goto WRONG_PASSWORD_LABEL;
    }
    
    if (password[1] != '0')
    {
        sCases[ONE_DIGIT_INDEX][1] = 1;
    }

    if (IsLastTwoDigitAlphabet(password, 1))
    {
        sCases[TWO_DIGIT_INDEX][1] = 1;
    }

    for (unsigned int i = 2; i < password.size(); ++i)
    {
        if (IsCorrectPassword(password, i) == false)
        {
            goto WRONG_PASSWORD_LABEL;
        }

        if (password[i] != '0')
        {
            sCases[ONE_DIGIT_INDEX][i] = (sCases[ONE_DIGIT_INDEX][i - 1] + sCases[TWO_DIGIT_INDEX][i - 1]) % CASE_DIVISOR;
        }

        if (IsLastTwoDigitAlphabet(password, i))
        {
            sCases[TWO_DIGIT_INDEX][i] = (sCases[ONE_DIGIT_INDEX][i - 2] + sCases[TWO_DIGIT_INDEX][i - 2]) % CASE_DIVISOR;
        }
    }

    std::cout << ((sCases[ONE_DIGIT_INDEX][password.size() - 1] + sCases[TWO_DIGIT_INDEX][password.size() - 1]) % CASE_DIVISOR);

    return 0;

WRONG_PASSWORD_LABEL:
    std::cout << 0;

    return 0;
}