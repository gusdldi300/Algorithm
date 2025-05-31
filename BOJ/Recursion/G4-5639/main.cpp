
#include <iostream>

#define MAX_NODE_COUNT (10000)

void PrintBSTPostOrderedRecursive(const unsigned int startIndex, const unsigned int endIndex, const unsigned int* preorderedNodes)
{
    if (startIndex > endIndex)
    {
        return;
    }

    unsigned int midNodeKey = preorderedNodes[startIndex];
    unsigned int nextEndIndex = endIndex;
    for (unsigned int i = startIndex + 1; i <= endIndex; ++i)
    {
        if (midNodeKey < preorderedNodes[i])
        {
            nextEndIndex = i - 1;
            break;
        }
    }

    PrintBSTPostOrderedRecursive(startIndex + 1, nextEndIndex, preorderedNodes);
    PrintBSTPostOrderedRecursive(nextEndIndex + 1, endIndex, preorderedNodes);
    std::cout << midNodeKey << std::endl;
}

int main()
{
    unsigned int preorderedNodes[MAX_NODE_COUNT];

    unsigned int newKey = 0;
    unsigned int nodesIndex = 0;

    while (true)
    {
        std::cin >> newKey;
        if (std::cin.eof())
        {
            break;
        }

        preorderedNodes[nodesIndex++] = newKey;
    }

    PrintBSTPostOrderedRecursive(0, nodesIndex - 1, preorderedNodes);

    return 0;
}

