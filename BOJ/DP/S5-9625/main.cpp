
#include <iostream>

#define MAX_LETTER_SIZE (2U)
#define MAX_BUTTON_COUNT (45U)

enum class Letter : unsigned int
{
    A = 0,
    B
};

int main()
{
    unsigned int letters[MAX_LETTER_SIZE][MAX_BUTTON_COUNT] = { 0, };
    
    unsigned int letterAIndex = static_cast<unsigned int>(Letter::A);
    unsigned int letterBIndex = static_cast<unsigned int>(Letter::B);
    letters[letterAIndex][0] = 0;
    letters[letterBIndex][0] = 1;

    unsigned int targetButtonCount = 0;
    std::cin >> targetButtonCount;

    for (unsigned int i = 1; i < targetButtonCount; ++i)
    {
        unsigned int lastLetterACount = letters[letterAIndex][i - 1];
        unsigned int lastLetterBCount = letters[letterBIndex][i - 1];

        letters[letterAIndex][i] = lastLetterBCount;
        letters[letterBIndex][i] = lastLetterACount + lastLetterBCount;
    }

    std::cout << letters[letterAIndex][targetButtonCount - 1] << ' ' << letters[letterBIndex][targetButtonCount - 1];

    return 0;
}