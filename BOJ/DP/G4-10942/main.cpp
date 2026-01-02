
#include <iostream>

#define MAX_SEQUENCE_SIZE (2001U)

static unsigned int sSequence[MAX_SEQUENCE_SIZE];
static bool sbPalindrome[MAX_SEQUENCE_SIZE][MAX_SEQUENCE_SIZE] = { false, };

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int sequenceSize;
    std::cin >> sequenceSize;

    for (unsigned int i = 0; i < sequenceSize; ++i)
    {
        std::cin >> sSequence[i];
        sbPalindrome[i][i] = true;
    }

    for (unsigned int startIndex = 0; startIndex < sequenceSize - 1; ++startIndex)
    {
        unsigned int endIndex = startIndex + 1;

        sbPalindrome[startIndex][endIndex] = ((sSequence[startIndex] == sSequence[endIndex]) ? true : false);
    }

    for (unsigned int offset = 2; offset < sequenceSize; ++offset)
    {
        for (unsigned int startIndex = 0; startIndex < (sequenceSize - offset); ++startIndex)
        {
            unsigned int endIndex = startIndex + offset;

            if (sbPalindrome[startIndex + 1][endIndex - 1] == false ||
                sSequence[startIndex] != sSequence[endIndex])
            {
                sbPalindrome[startIndex][endIndex] = false;
                
                continue;
            }
            
            sbPalindrome[startIndex][endIndex] = true;
        }
    }

    unsigned int questionsCount;
    std::cin >> questionsCount;

    for (unsigned int i = 0; i < questionsCount; ++i)
    {
        std::pair<unsigned int, unsigned int> question;
        std::cin >> question.first >> question.second;

        std::cout << (sbPalindrome[question.first - 1][question.second - 1] ? 1 : 0) << '\n';
    }

    return 0;
}