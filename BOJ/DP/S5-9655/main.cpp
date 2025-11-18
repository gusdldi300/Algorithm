
#include <iostream>
#include <cmath>

#define MAX_PLAYER_COUNT (2U)
#define MAX_STONE_COUNT (1000U)

enum class Player : unsigned int
{
    None = 0,
    Sk,
    Cy,
};

static Player GetStoneGameWinner(unsigned int stoneCount, Player player, Player opponent, Player cache[][MAX_STONE_COUNT])
{
    if (stoneCount == 1 || stoneCount == 3)
    {
        return player;
    }

    unsigned int playerIndex = static_cast<unsigned int>(player) - 1;
    if (cache[playerIndex][stoneCount] != Player::None)
    {
        return cache[playerIndex][stoneCount];
    }

    Player winner = GetStoneGameWinner(stoneCount - 1, opponent, player, cache);
    if (stoneCount > 3)
    {
        Player candidate = GetStoneGameWinner(stoneCount - 3, opponent, player, cache);
        
        winner = (player == winner ? winner : candidate);
    }

    cache[playerIndex][stoneCount] = winner;

    return winner;
}

int main()
{
    unsigned int targetStoneCount = 0;
    std::cin >> targetStoneCount;

    Player cache[MAX_PLAYER_COUNT][MAX_STONE_COUNT] = { Player::None, };
    
    Player winner = GetStoneGameWinner(targetStoneCount, Player::Sk, Player::Cy, cache);
    std::cout << (winner == Player::Sk ? "SK" : "CY");

    return 0;
}
