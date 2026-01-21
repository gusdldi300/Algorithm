
#include <climits>
#include <iostream>

#define MAX_ARRAY_SIZE (200U)

static int GetMaxContinuousSumFrom(const int* array, unsigned int arraySize)
{

    int continuousSum = array[0];
    int maxContinuousSum = continuousSum;

    for (unsigned int i = 1; i < arraySize; ++i)
    {
        if (continuousSum < 0)
        {
            continuousSum = 0;
        }

        continuousSum += array[i];
        maxContinuousSum = std::max(maxContinuousSum, continuousSum);
    }

    return maxContinuousSum;
}

int main()
{
    unsigned int arraySizeRow;
    unsigned int arraySizeCol;

    std::cin >> arraySizeRow >> arraySizeCol;

    int array[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0, };

    for (unsigned int row = 0; row < arraySizeRow; ++row)
    {
        for (unsigned int col = 0; col < arraySizeCol; ++col)
        {
            std::cin >> array[row][col];
        }
    }

    int maxSubArraySum = INT_MIN;
    for (unsigned int startCol = 0; startCol < arraySizeCol; ++startCol)
    {
        int subArraySums[MAX_ARRAY_SIZE] = { 0, };

        for (unsigned int endCol = startCol; endCol < arraySizeCol; ++endCol)
        {
            // Kadene algorithm
            for (unsigned int row = 0; row < arraySizeRow; ++row)
            {
                subArraySums[row] += array[row][endCol];
            }

            int subArraySum = GetMaxContinuousSumFrom(subArraySums, arraySizeRow);
            maxSubArraySum = std::max(maxSubArraySum, subArraySum);
        }
    }

    std::cout << maxSubArraySum;

    return 0;
}