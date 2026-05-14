
#include <cstring>
#include <iostream>
#include <vector>

#define MAX_CARDS_COUNT (1001U)

struct Score
{
    unsigned int A;
    unsigned int B;
};

static Score GetMaxScoreRecursive(unsigned int leftCount, unsigned int rightCount, bool bTurn, Score maxScores[MAX_CARDS_COUNT][MAX_CARDS_COUNT], const std::vector<unsigned int>& cards)
{
    unsigned int leftIndex = leftCount;
    unsigned int rightIndex = cards.size() - rightCount - 1;
    if (leftIndex == rightIndex)
    {
        if (bTurn)
        {
            return { cards[leftIndex], 0 };
        }

        return { 0, cards[leftIndex] };
    }

    if (maxScores[leftCount][rightCount].A > 0 || maxScores[leftCount][rightCount].B > 0)
    {
        return maxScores[leftCount][rightCount];
    }

    bool bNextTurn = bTurn ? false : true;

    Score leftScore = GetMaxScoreRecursive(leftCount + 1, rightCount, bNextTurn, maxScores, cards);
    Score rightScore = GetMaxScoreRecursive(leftCount, rightCount + 1, bNextTurn, maxScores, cards);

    Score maxScore;
    if (bTurn)
    {
        leftScore.A += cards[leftIndex];
        rightScore.A += cards[rightIndex];

        if (leftScore.A < rightScore.A)
        {
            maxScore = rightScore;
        }
        else
        {
            maxScore = leftScore;
        }
    }
    else
    {
        leftScore.B += cards[leftIndex];
        rightScore.B += cards[rightIndex];

        if (leftScore.B < rightScore.B)
        {
            maxScore = rightScore;
        }
        else
        {
            maxScore = leftScore;
        }
    }

    maxScores[leftCount][rightCount] = maxScore;

    return maxScore;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int testsCount;
    std::cin >> testsCount;

    Score maxScores[MAX_CARDS_COUNT][MAX_CARDS_COUNT] = { 0, };

    for (unsigned int i = 0; i < testsCount; ++i)
    {
        unsigned int cardsCount;
        std::cin >> cardsCount;

        std::vector<unsigned int> cards;
        for (unsigned int j = 0; j < cardsCount; ++j)
        {
            unsigned int card;
            std::cin >> card;

            cards.push_back(card);
        }

        memset(maxScores, 0, sizeof(maxScores));
        Score maxScore = GetMaxScoreRecursive(0, 0, true, maxScores, cards);

        std::cout << maxScore.A << '\n';
    }

    return 0;
}