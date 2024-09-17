
#include <iostream>
#include <list>
#include <vector>

#define MAX_BOARD_SIZE (12)
#define MAX_PLAYERS_SIZE (10)
#define MAX_TURN (1000)

typedef struct {
	int Row;
	int Col;
} Position;

typedef struct {
	unsigned int Id;
	unsigned int Direction;
} Player;

static unsigned int sBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
static std::list<Player> sPlayerBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

static Position sPlayerPositions[MAX_PLAYERS_SIZE];

static unsigned int sBoardSize;
static unsigned int sPlayerSize;

static Position sDirections[] = { { 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 } };

static bool IsUnreachablePosition(int row, int col)
{
	if (row < 0 || row >= static_cast<int>(sBoardSize) || col < 0 || col >= static_cast<int>(sBoardSize) || sBoard[row][col] == 2)
	{
		return true;
	}

	return false;
}

int main()
{
	std::cin >> sBoardSize >> sPlayerSize;

	for (unsigned int row = 0; row < sBoardSize; ++row)
	{
		for (unsigned int col = 0; col < sBoardSize; ++col)
		{
			std::cin >> sBoard[row][col];
		}
	}

	for (unsigned int i = 0; i < sPlayerSize; ++i)
	{
		unsigned int curRow;
		unsigned int curCol;
		unsigned int curDirection;

		std::cin >> curRow >> curCol >> curDirection;

		sPlayerPositions[i].Row = curRow - 1;
		sPlayerPositions[i].Col = curCol - 1;

		Player player;
		player.Id = i;
		player.Direction = curDirection - 1;

		sPlayerBoard[sPlayerPositions[i].Row][sPlayerPositions[i].Col].push_back(player);
	}

	// Start game
	unsigned int turn = 1;
	bool bComplete = false;

	while (turn <= MAX_TURN)
	{
		for (unsigned int id = 0; id < sPlayerSize; ++id)
		{
			unsigned int playerRow = sPlayerPositions[id].Row;
			unsigned int playerCol = sPlayerPositions[id].Col;

			std::list<Player>& curPositionList = sPlayerBoard[playerRow][playerCol]; // never empty
			if (curPositionList.front().Id != id)
			{
				continue;
			}

			Player& curPlayer = curPositionList.front();
			int nextRow = static_cast<int>(playerRow) + sDirections[curPlayer.Direction].Row;
			int nextCol = static_cast<int>(playerCol) + sDirections[curPlayer.Direction].Col;

			if (IsUnreachablePosition(nextRow, nextCol))
			{
				if (curPlayer.Direction == 1 || curPlayer.Direction == 3)
				{
					curPlayer.Direction--;
				}
				else
				{
					curPlayer.Direction++;
				}

				nextRow = static_cast<int>(playerRow) + sDirections[curPlayer.Direction].Row;
				nextCol = static_cast<int>(playerCol) + sDirections[curPlayer.Direction].Col;

				if (IsUnreachablePosition(nextRow, nextCol))
				{
					continue;
				}
			}

			if (sBoard[nextRow][nextCol] == 0)
			{
				while (curPositionList.empty() == false)
				{
					Player nextPlayer = curPositionList.front();
					curPositionList.pop_front();

					sPlayerBoard[nextRow][nextCol].push_back(nextPlayer);

					sPlayerPositions[nextPlayer.Id].Row = nextRow;
					sPlayerPositions[nextPlayer.Id].Col = nextCol;
				}
			}
			else
			{
				while (curPositionList.empty() == false)
				{
					Player nextPlayer = curPositionList.back();
					curPositionList.pop_back();

					sPlayerBoard[nextRow][nextCol].push_back(nextPlayer);

					sPlayerPositions[nextPlayer.Id].Row = nextRow;
					sPlayerPositions[nextPlayer.Id].Col = nextCol;
				}
			}

			if (sPlayerBoard[nextRow][nextCol].size() >= 4)
			{
				bComplete = true;
				goto outer;
			}
		}

		++turn;
	}

outer:
	if (bComplete)
	{
		std::cout << turn;
	}
	else
	{
		std::cout << -1;
	}

	return 0;
}