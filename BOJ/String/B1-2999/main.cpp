
#include <iostream>

#define MAX_MESSAGE_SIZE (101U)

int main()
{
    std::string encryptedMessage;
    std::cin >> encryptedMessage;

    unsigned int maxRowSize = 0;
    unsigned int maxColSize = 0;

    for (unsigned int rowSize = 1; rowSize < MAX_MESSAGE_SIZE; ++rowSize)
    {
        if ((encryptedMessage.size() % rowSize) == 0)
        {
            unsigned int colSize = encryptedMessage.size() / rowSize;
            if (rowSize > colSize)
            {
                break;
            }

            maxRowSize = rowSize;
            maxColSize = colSize;
        }
    }

    // r = 2, c = 3
    // kak
    // osi
    // koaski

    std::string decryptedMessage;
    unsigned int encyptedIndex = 0;
    for (unsigned int row = 0; row < maxRowSize; ++row)
    {
        for (unsigned int col = 0; col < maxColSize; ++col)
        {
            decryptedMessage.push_back(encryptedMessage[row + (col * maxRowSize)]);
        }
    } 

    std::cout << decryptedMessage;

    return 0;
}