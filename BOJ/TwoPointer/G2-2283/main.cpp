#include <iostream>
#include <cstring>

#define MAX_LINE_LENGTH (1000000U)
//#define MAX_LINE_LENGTH (15U)

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int linesCount;
    long long targetLength;
    std::cin >> linesCount >> targetLength;

    long long* pLinePoints = new long long[MAX_LINE_LENGTH + 1];
    memset(pLinePoints, 0, sizeof(long long) * (MAX_LINE_LENGTH + 1));

    for (unsigned int i = 0; i < linesCount; ++i)
    {
        unsigned int startLineIndex;
        unsigned int endLineIndex;

        std::cin >> startLineIndex >> endLineIndex;
        pLinePoints[startLineIndex]++;
        pLinePoints[endLineIndex]--;
    }

    for (unsigned int i = 0; i < MAX_LINE_LENGTH; ++i)
    {
        pLinePoints[i + 1] += pLinePoints[i];
    }

    unsigned int leftIndex = 0;
    unsigned int rightIndex = 1;

    long long totalLength = pLinePoints[leftIndex];
    while (true)
    {
        if (totalLength == targetLength)
        {
            std::cout << leftIndex << ' ' << rightIndex;

            goto OUT_LABEL;
        }

        if (totalLength < targetLength)
        {
            if (rightIndex >= MAX_LINE_LENGTH)
            {
                break;
            }

            totalLength += pLinePoints[rightIndex];

            rightIndex++;
        }
        else
        {
            totalLength -= pLinePoints[leftIndex];

            leftIndex++;
        }
    }

    std::cout << "0 0";

OUT_LABEL:
    delete[] pLinePoints;

    return 0;
}