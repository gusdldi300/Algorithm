#include <iostream>
#include <vector>

int main()
{
    unsigned int targetNumber;
    std::cin >> targetNumber;

    // Get prime numbers
    
    std::vector<bool> bPrimeNumbers;
    bPrimeNumbers.assign(targetNumber + 1, true);

    bPrimeNumbers[0] = false;
    bPrimeNumbers[1] = false;

    for (unsigned int number = 0; number * number <= targetNumber; ++number)
    {
        if (bPrimeNumbers[number] == false)
        {
            continue;
        }

        for (unsigned int compositeNumber = number * number; compositeNumber <= targetNumber; compositeNumber += number)
        {
            bPrimeNumbers[compositeNumber] = false;
        }
    }

    std::vector<unsigned int> primeNumbersAscend;
    for (unsigned int number = 2; number <= targetNumber; ++number)
    {
        if (bPrimeNumbers[number])
        {
            primeNumbersAscend.push_back(number);
        }
    }

    unsigned int casesCount = 0;

    unsigned int startIndex = 0;
    unsigned int continuosSum = 0;
    for (unsigned int endIndex = 0; endIndex < primeNumbersAscend.size(); ++endIndex)
    {
        continuosSum += primeNumbersAscend[endIndex];

        for (startIndex; startIndex <= endIndex; ++startIndex)
        {
            if (continuosSum == targetNumber)
            {
                ++casesCount;
            }
            else if (continuosSum < targetNumber)
            {
                break;
            }

            continuosSum -= primeNumbersAscend[startIndex];
        }
    }

    std::cout << casesCount;

    return 0;
}