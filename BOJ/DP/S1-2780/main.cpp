
#include <iostream>
#include <vector>

#define MAX_MACHINE_SIZE_ROW (4U)
#define MAX_MACHINE_SIZE_COL (3U)
#define MAX_PASSWORD_SIZE (1001U)
#define CASE_DIVISOR (1234567U)
#define MAX_NUMBER (9U)
#define MAX_DIRECTIONS_SIZE (4U)

static const int MOVE_DIRECTIONS[MAX_DIRECTIONS_SIZE][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static std::vector<unsigned int> sNumbers[MAX_NUMBER + 1];
static unsigned int sPaths[MAX_PASSWORD_SIZE][MAX_NUMBER + 1] = { 0, };

int main()
{
    sNumbers[0].push_back(7);
    
    sNumbers[1].push_back(2);
    sNumbers[1].push_back(4);
    
    sNumbers[2].push_back(1);
    sNumbers[2].push_back(3);
    sNumbers[2].push_back(5);

    sNumbers[3].push_back(2);
    sNumbers[3].push_back(6);

    sNumbers[4].push_back(1);
    sNumbers[4].push_back(5);
    sNumbers[4].push_back(7);

    sNumbers[5].push_back(2);
    sNumbers[5].push_back(6);
    sNumbers[5].push_back(8);
    sNumbers[5].push_back(4);

    sNumbers[6].push_back(3);
    sNumbers[6].push_back(5);
    sNumbers[6].push_back(9);

    sNumbers[7].push_back(4);
    sNumbers[7].push_back(8);
    sNumbers[7].push_back(0);

    sNumbers[8].push_back(5);
    sNumbers[8].push_back(9);
    sNumbers[8].push_back(7);
    
    sNumbers[9].push_back(6);
    sNumbers[9].push_back(8);

    for (unsigned int number = 0; number <= MAX_NUMBER; ++number)
    {
        sPaths[1][number] = 1;
    }

    for (unsigned int length = 1; length < MAX_PASSWORD_SIZE - 1; ++length)
    {
        for (unsigned int number = 0; number <= MAX_NUMBER; ++number)
        {
            std::vector<unsigned int>& attachedNumbers = sNumbers[number];
            unsigned int nextLength = length + 1;

            for (unsigned int nextNumber : attachedNumbers)
            {
                sPaths[nextLength][nextNumber] = (sPaths[nextLength][nextNumber] + sPaths[length][number]) % CASE_DIVISOR;
            }
        }
    }

    unsigned int testCount = 0;
    std::cin >> testCount;
    
    for (unsigned int test = 0; test < testCount; ++test)
    {
        unsigned int passwordSize = 0;
        std::cin >> passwordSize;

        unsigned int caseCount = 0;
        for (unsigned int number = 0; number <= MAX_NUMBER; ++number)
        {
            caseCount = (caseCount + sPaths[passwordSize][number]) % CASE_DIVISOR;
        }

        std::cout << caseCount << std::endl;
    }
    

    return 0;
}