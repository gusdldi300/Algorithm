
#include <iostream>

#define MAX_NUMBERS_COUNT (100001U)

#define NONE (0U)
#define ROOT_INDEX (1U)

static void SwapNumber(unsigned int firstIndex, unsigned int secondIndex, unsigned int outNumbers[])
{
    unsigned int tempNumber = outNumbers[firstIndex];
    outNumbers[firstIndex] = outNumbers[secondIndex];
    outNumbers[secondIndex] = tempNumber;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int numbers[MAX_NUMBERS_COUNT] = { NONE, };
    
    unsigned int operationsCount;
    std::cin >> operationsCount;
    
    unsigned int lastIndex = 0;
    for (unsigned int i = 0; i < operationsCount; ++i)
    {
        unsigned int operation;
        std::cin >> operation;

        if (operation == 0)
        {
            // Pop
            {
                if (lastIndex == 0)
                {
                    std::cout << NONE << '\n';

                    continue;
                }

                std::cout << numbers[ROOT_INDEX] << '\n';

                unsigned int index = ROOT_INDEX;
                numbers[index] = numbers[lastIndex];
                numbers[lastIndex] = NONE;
                --lastIndex;

                while (true)
                {
                    unsigned int leftChildIndex = index * 2;
                    // Empty
                    if (leftChildIndex > lastIndex)
                    {
                        break;
                    }

                    unsigned int rightChildIndex = leftChildIndex + 1;
                    unsigned int minChildIndex = 0;
                    if (rightChildIndex > lastIndex || numbers[leftChildIndex] <= numbers[rightChildIndex])
                    {
                        if (numbers[index] <= numbers[leftChildIndex])
                        {
                            break;
                        }

                        minChildIndex = leftChildIndex;
                    }
                    else
                    {
                        if (numbers[index] <= numbers[rightChildIndex])
                        {
                            break;
                        }

                        minChildIndex = rightChildIndex;
                    }

                    SwapNumber(index, minChildIndex, numbers);
                    index = minChildIndex;
                }
            }

            continue;
        }

        // Push
        {
            ++lastIndex;
            numbers[lastIndex] = operation;
            unsigned int index = lastIndex;

            while (true)
            {
                unsigned int parentIndex = index / 2;
                if (parentIndex < ROOT_INDEX)
                {
                    break;
                }

                if (numbers[index] >= numbers[parentIndex])
                {
                    break;
                }

                SwapNumber(index, parentIndex, numbers);
                index = parentIndex;
            }
        }
    }

    return 0;
}