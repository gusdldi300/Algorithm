
#include <iostream>

#define MAX_CLOSETS_COUNT (21U)

static unsigned int sMinClosetUseMoves[MAX_CLOSETS_COUNT][MAX_CLOSETS_COUNT][MAX_CLOSETS_COUNT] = { 0, };
static unsigned int sUseClosets[MAX_CLOSETS_COUNT] = { 0, };

static unsigned int sUseClosetsCount;

static unsigned int GetMinClosetUseMovesRecursive(unsigned int useClosetsIndex, unsigned int leftUseCloset, unsigned int rightUseCloset)
{
    if (useClosetsIndex >= sUseClosetsCount)
    {
        return 0;
    }

    if (sMinClosetUseMoves[useClosetsIndex][leftUseCloset][rightUseCloset] > 0)
    {
        return sMinClosetUseMoves[useClosetsIndex][leftUseCloset][rightUseCloset];
    }

    unsigned int moveCount = 0;
    unsigned int useCloset = sUseClosets[useClosetsIndex];
    if (useCloset <= leftUseCloset)
    {
        moveCount = leftUseCloset - useCloset;
        moveCount += GetMinClosetUseMovesRecursive(useClosetsIndex + 1, useCloset, rightUseCloset);
    }
    else if (useCloset >= rightUseCloset)
    {
        moveCount = useCloset - rightUseCloset;
        moveCount += GetMinClosetUseMovesRecursive(useClosetsIndex + 1, leftUseCloset, useCloset);
    }
    else
    {
        unsigned int leftMoveCount = useCloset - leftUseCloset;
        leftMoveCount += GetMinClosetUseMovesRecursive(useClosetsIndex + 1, useCloset, rightUseCloset);

        unsigned int rightMoveCount = rightUseCloset - useCloset;
        rightMoveCount += GetMinClosetUseMovesRecursive(useClosetsIndex + 1, leftUseCloset, useCloset);

        moveCount = std::min(leftMoveCount, rightMoveCount);
    }

    sMinClosetUseMoves[useClosetsIndex][leftUseCloset][rightUseCloset] = moveCount;
    return moveCount;
}

int main()
{
    unsigned int closetsCount;
    std::cin >> closetsCount;

    unsigned int leftOpenCloset;
    unsigned int rightOpenCloset;

    std::cin >> leftOpenCloset >> rightOpenCloset;
    std::cin >> sUseClosetsCount;

    for (unsigned int i = 0; i < sUseClosetsCount; ++i)
    {
        std::cin >> sUseClosets[i];
    }

    unsigned int moveCount = 0;
    if (leftOpenCloset < rightOpenCloset)
    {
        moveCount = GetMinClosetUseMovesRecursive(0, leftOpenCloset, rightOpenCloset);
    }
    else
    {
        moveCount = GetMinClosetUseMovesRecursive(0, rightOpenCloset, leftOpenCloset);
    }

    std::cout << moveCount;

    return 0;
}