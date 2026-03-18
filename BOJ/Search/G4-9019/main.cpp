
#include <iostream>
#include <unordered_map>
#include <queue>
#include <cassert>
#include <stack>

struct PathInfo
{
    char Operation;
    unsigned int LastNumber;
};

#define MAX_NUMBER (10000U)
#define FIRST_DIGIT_DIVISOR (10U)
#define LAST_DIGIT_DIVISOR (1000U)

static const std::vector<char> OPERATIONS = { 'D', 'S', 'L', 'R' };

unsigned int CalculateNumber(unsigned int number, char operation)
{
    unsigned int calculatedNumber = number;
    
    switch (operation)
    {
    case 'D':
    {
        calculatedNumber = (calculatedNumber * 2) % MAX_NUMBER;

        break;
    }
    case 'S':
    {
        if (calculatedNumber == 0)
        {
            calculatedNumber = MAX_NUMBER - 1;

            break;
        }

        --calculatedNumber;

        break;
    }
    case 'L':
    {
        unsigned int lastDigit = calculatedNumber / LAST_DIGIT_DIVISOR;
        calculatedNumber = (calculatedNumber % LAST_DIGIT_DIVISOR) * FIRST_DIGIT_DIVISOR;

        calculatedNumber += lastDigit;

        break;
    }
    case 'R':
    {
        unsigned int firstDigit = calculatedNumber % FIRST_DIGIT_DIVISOR;
        calculatedNumber /= FIRST_DIGIT_DIVISOR;

        calculatedNumber = calculatedNumber + (firstDigit * LAST_DIGIT_DIVISOR);

        break;
    }
    default:
    {
        assert(false);
    }
    }

    return calculatedNumber;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int i = 0; i < testsCount; ++i)
    {
        unsigned int startNumber;
        unsigned int targetNumber;
        std::cin >> startNumber >> targetNumber;
        
        bool bVisited[MAX_NUMBER] = { false, };
        PathInfo pathInfos[MAX_NUMBER];

        bVisited[startNumber] = true;
        
        std::queue<unsigned int> numberQueue;
        numberQueue.push(startNumber);

        while (numberQueue.empty() == false)
        {
            unsigned int number = numberQueue.front();
            numberQueue.pop();

            if (number == targetNumber)
            {
                break;
            }

            for (unsigned int calculateIndex = 0; calculateIndex < OPERATIONS.size(); ++calculateIndex)
            {
                char nextOperation = OPERATIONS[calculateIndex];
                
                unsigned int calculatedNumber = CalculateNumber(number, nextOperation);
                if (bVisited[calculatedNumber])
                {
                    continue;
                }

                bVisited[calculatedNumber] = true;
                pathInfos[calculatedNumber] = { nextOperation, number };

                numberQueue.push(calculatedNumber);
            }
        }

        std::stack<char> operationStack;
        unsigned int lastNumber = targetNumber;
        while (true)
        {
            PathInfo pathInfo = pathInfos[lastNumber];
            operationStack.push(pathInfo.Operation);
            
            if (pathInfo.LastNumber == startNumber)
            {
                break;
            }

            lastNumber = pathInfo.LastNumber;
        }

        std::string targetOperations;
        while (operationStack.empty() == false)
        {
            targetOperations.push_back(operationStack.top());
            operationStack.pop();
        }
        
        std::cout << targetOperations << '\n';
    }

    return 0;
}
