
#include <iostream>

#define PARTITION_SIZE (4U)
#define MAX_PARTITION_COUNT (8U)

static void FillZerosTo(std::string* outAddress, unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i)
    {
        outAddress->push_back('0');
    }
}

static void DecodeAddress(const std::string& encodedIPv6, unsigned int startIndex, unsigned int length, std::string* outDecodedIPv6)
{
    if (length == 0)
    {
        return;
    }

    std::string partitionAddress;

    for (unsigned int i = startIndex; i < (startIndex + length); ++i)
    {
        char digit = encodedIPv6[i];
        if (digit == ':')
        {
            FillZerosTo(outDecodedIPv6, PARTITION_SIZE - partitionAddress.size());
            outDecodedIPv6->append(partitionAddress);
            outDecodedIPv6->push_back(':');

            partitionAddress.clear();

            continue;
        }

        partitionAddress.push_back(digit);
    }

    if (encodedIPv6[startIndex + length - 1] != ':')
    {
        FillZerosTo(outDecodedIPv6, PARTITION_SIZE - partitionAddress.size());
        outDecodedIPv6->append(partitionAddress);
    }

    outDecodedIPv6->push_back(':');
}

int main()
{
    std::string encodedIPv6;
    std::cin >> encodedIPv6;

    unsigned int secondRuleStartIndex = encodedIPv6.find("::");

    std::string decodedIPv6;

    unsigned int partitionCount = 0;
    if (secondRuleStartIndex != -1)
    {
        bool bLastNumber = false;
        for (unsigned int i = 0; i < encodedIPv6.size(); ++i)
        {
            if (encodedIPv6[i] == ':')
            {
                if (bLastNumber)
                {
                    partitionCount++;
                }

                bLastNumber = false;
                continue;
            }

            bLastNumber = true;
        }

        if (bLastNumber)
        {
            partitionCount++;
        }

        DecodeAddress(encodedIPv6, 0, secondRuleStartIndex - 0, &decodedIPv6);

        for (unsigned int j = 0; j < MAX_PARTITION_COUNT - partitionCount; ++j)
        {
            FillZerosTo(&decodedIPv6, PARTITION_SIZE);
            decodedIPv6.push_back(':');
        }

        unsigned int secondRuleEndIndex = secondRuleStartIndex + 2;
        DecodeAddress(encodedIPv6, secondRuleEndIndex, encodedIPv6.size() - secondRuleEndIndex, &decodedIPv6);
    }
    else
    {
        DecodeAddress(encodedIPv6, 0, encodedIPv6.size(), &decodedIPv6);
    }

    if (decodedIPv6[decodedIPv6.size() - 1] == ':')
    {
        decodedIPv6.pop_back();
    }

    std::cout << decodedIPv6;

    return 0;
}