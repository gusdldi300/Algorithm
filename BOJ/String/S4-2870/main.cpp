
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#define MAX_SENTENCE_LENGTH (101U)

struct StringNumberComparer
{
    bool operator()(const std::string& first, const std::string& second)
    {
        if (first.size() != second.size())
        {
            return first.size() > second.size();
        }

        return (first <= second) ? false : true;
    }
};

int main()
{
    unsigned int sentencesCount;
    std::cin >> sentencesCount;
    
    std::vector<std::string> numberStrings;
    std::priority_queue<std::string, std::vector<std::string>, StringNumberComparer> numberStringAscendQueue;

    for (unsigned int i = 0; i < sentencesCount; ++i)
    {
        std::string sentence;
        sentence.reserve(MAX_SENTENCE_LENGTH);
        
        std::cin >> sentence;

        std::string numberString;
        numberString.reserve(MAX_SENTENCE_LENGTH);

        bool bNumber = false;
        for (unsigned int sentenceIndex = 0; sentenceIndex < sentence.size(); ++sentenceIndex)
        {
            char checkChar = sentence[sentenceIndex];

            if (checkChar >= '0' && checkChar <= '9')
            {
                if (bNumber == false)
                {
                    bNumber = true;
                }

                numberString.push_back(checkChar);

                continue;
            }

            if (bNumber)
            {
                bNumber = false;

                numberStrings.push_back(numberString);
                numberString.clear();
            }
        }

        if (numberString.empty() == false)
        {
            numberStrings.push_back(numberString);
        }
    }

    for (const std::string& rawNumber : numberStrings)
    {
        std::string fixedNumberString;
        fixedNumberString.reserve(MAX_SENTENCE_LENGTH);

        bool bPrefix = rawNumber[0] == '0' ? true : false;
        for (unsigned int numberIndex = 0; numberIndex < rawNumber.size(); ++numberIndex)
        {
            char checkChar = rawNumber[numberIndex];

            if (bPrefix && checkChar == '0')
            {
                continue;
            }

            fixedNumberString.push_back(checkChar);
            bPrefix = false;
        }

        if (fixedNumberString.empty())
        {
            fixedNumberString.push_back('0');
        }

        numberStringAscendQueue.push(fixedNumberString);
    }

    while (numberStringAscendQueue.empty() == false)
    {
        std::cout << numberStringAscendQueue.top() << std::endl;
        numberStringAscendQueue.pop();
    }

    return 0;
}