#include <iostream>

#define MAX_PLAYERS_SIZE (16)

static int sPlayerGuiltScores[MAX_PLAYERS_SIZE];
static bool sbPlayerDead[MAX_PLAYERS_SIZE] = { false, };

static unsigned int sPlayersSize;

static int sGuilts[MAX_PLAYERS_SIZE][MAX_PLAYERS_SIZE];
static unsigned int sMafiaIndex;

static unsigned int sMostSurvivedDays = 0;

bool IsDead(unsigned int playerIndex)
{
	return sbPlayerDead[playerIndex] ? true : false;
}

bool getMostSurvivedDaysRecursive(unsigned int survivedDays, unsigned int survivedPlayers)
{
	if (survivedPlayers == 1)
	{
		sMostSurvivedDays = survivedDays;

		return true;
	}
	
	if (survivedPlayers % 2 == 0)
	{
		for (unsigned int killIndex = 0; killIndex < sPlayersSize; ++killIndex)
		{
			if (IsDead(killIndex) || killIndex == sMafiaIndex)
			{
				continue;
			}

			sbPlayerDead[killIndex] = true;
			for (int i = 0; i < sPlayersSize; ++i)
			{
				sPlayerGuiltScores[i] += sGuilts[killIndex][i];
			}

			if (getMostSurvivedDaysRecursive(survivedDays + 1, survivedPlayers - 1))
			{
				return true;
			}
			
			sbPlayerDead[killIndex] = false;
			for (int i = 0; i < sPlayersSize; ++i)
			{
				sPlayerGuiltScores[i] -= sGuilts[killIndex][i];
			}
		}
	}
	else
	{
		int mostGuiltScore = 0;
		int mostGuiltyPlayerIndex = -1;
		for (int i = 0; i < sPlayersSize; ++i)
		{
			if (IsDead(i))
			{
				continue;
			}

			if (sPlayerGuiltScores[i] > mostGuiltScore)
			{
				mostGuiltScore = sPlayerGuiltScores[i];
				mostGuiltyPlayerIndex = i;
			}
		}

		if (sMafiaIndex == mostGuiltyPlayerIndex)
		{
			if (survivedDays > sMostSurvivedDays) {
				sMostSurvivedDays = survivedDays;
			}

			return false;
		}

		sbPlayerDead[mostGuiltyPlayerIndex] = true;

		if (getMostSurvivedDaysRecursive(survivedDays, survivedPlayers - 1))
		{
			return true;
		}

		sbPlayerDead[mostGuiltyPlayerIndex] = false;
	}

	return false;
}

int main()
{
	std::cin >> sPlayersSize;
	
	for (unsigned int i = 0; i < sPlayersSize; ++i)
	{
		std::cin >> sPlayerGuiltScores[i];
	}

	for (unsigned int row = 0; row < sPlayersSize; ++row)
	{
		for (unsigned int col = 0; col < sPlayersSize; ++col)
		{
			std::cin >> sGuilts[row][col];
		}
	}

	std::cin >> sMafiaIndex;

	// Start game
	getMostSurvivedDaysRecursive(0, sPlayersSize);
	std::cout << sMostSurvivedDays << std::endl;

	return 0;
}
