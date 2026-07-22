
#include "Common.h"

void Common::Swap(int* outNum, int* outOtherNum)
{
    if (outNum == outOtherNum)
    {
        return;
    }

    int temp = *outNum;
    *outNum = *outOtherNum;
    *outOtherNum = temp;
}
