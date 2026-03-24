#include <iostream>
#include <vector>
#include <cstring>

#define MAX_PLAYERS_COUNT (1001U)
#define MAX_SELECTED_PLAYERS (15U)

struct Player
{
    int White;
    int Black;
};

static unsigned int sPlayersCount = 0;
static int sMaxAbilities[MAX_PLAYERS_COUNT][MAX_SELECTED_PLAYERS + 2][MAX_SELECTED_PLAYERS + 2];

int main()
{
    std::vector<Player> players;
    while (true)
    {
        Player player;
        std::cin >> player.White >> player.Black;
        if (std::cin.eof())
        {
            break;
        }

        players.push_back(player);
    }

    sPlayersCount = players.size();

    memset(sMaxAbilities, -1, sizeof(sMaxAbilities));

    sMaxAbilities[0][0][0] = 0;
    sMaxAbilities[0][1][0] = players[0].White;
    sMaxAbilities[0][0][1] = players[0].Black;

    for (unsigned int player = 0; player < sPlayersCount - 1; ++player)
    {
        for (unsigned int whiteCount = 0; whiteCount <= MAX_SELECTED_PLAYERS; ++whiteCount)
        {
            for (unsigned int blackCount = 0; blackCount <= MAX_SELECTED_PLAYERS; ++blackCount)
            {
                if (sMaxAbilities[player][whiteCount][blackCount] == -1)
                {
                    break;
                }

                sMaxAbilities[player + 1][whiteCount][blackCount] = std::max(sMaxAbilities[player + 1][whiteCount][blackCount], sMaxAbilities[player][whiteCount][blackCount]);

                sMaxAbilities[player + 1][whiteCount + 1][blackCount] = std::max(sMaxAbilities[player + 1][whiteCount + 1][blackCount], sMaxAbilities[player][whiteCount][blackCount] + players[player + 1].White);
                sMaxAbilities[player + 1][whiteCount][blackCount + 1] = std::max(sMaxAbilities[player + 1][whiteCount][blackCount + 1], sMaxAbilities[player][whiteCount][blackCount] + players[player + 1].Black);
            }
        }
    }

    std::cout << sMaxAbilities[sPlayersCount - 1][MAX_SELECTED_PLAYERS][MAX_SELECTED_PLAYERS];

    return 0;
}