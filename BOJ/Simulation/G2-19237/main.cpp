#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

#define MAX_MAP_SIZE (20)
#define MAX_SHARKS_SIZE (400)
#define MAX_MOVE_DIRECTIONS (4)
#define MAX_TIME (1000)

typedef struct
{
	int Row;
	int Col;
} Position;

class Shark
{
public:
	Shark(int id, Position position, unsigned int direction);

public:
	int Id;
	Position CurPosition;
	unsigned int CurDirection;

	unsigned int PreferDirections[MAX_MOVE_DIRECTIONS][MAX_MOVE_DIRECTIONS];
};

Shark::Shark(int id, Position position, unsigned int direction)
	: Id(id)
	, CurPosition(position)
	, CurDirection(direction)
{
}

typedef struct
{
	int SharkId;
	int ScentId;
	unsigned int Count;
} Block;

typedef struct
{
	unsigned int Id;
	Position CurPosition;
	unsigned int StartDirection;
} SharkInfo;

static int sMapSize;
static unsigned int sSharksSize;
static unsigned int sTotalScentCount;

static Block sMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
static Position sMoveDirections[] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

static SharkInfo sSharkInfos[MAX_SHARKS_SIZE];

void PrintMap()
{
	std::cout << "Map" << std::endl;

	for (int row = 0; row < sMapSize; ++row)
	{
		for (int col = 0; col < sMapSize; ++col)
		{
			std::cout << sMap[row][col].ScentId << ", " << sMap[row][col].Count << " | ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void PrintDirection(unsigned int direction)
{
	std::string dirString;

	switch (direction)
	{
	case 0:
		dirString = "UP";
		break;
	case 1:
		dirString = "DOWN";
		break;
	case 2:
		dirString = "LEFT";
		break;
	case 3:
		dirString = "RIGHT";
		break;
	default:
		break;
	}

	std::cout << dirString;
}

void PrintShark(const Shark* shark)
{
	std::cout << "Shark: " << shark->Id << std::endl;
	std::cout << "(" << shark->CurPosition.Row << ", " << shark->CurPosition.Col << ")" << std::endl;
	PrintDirection(shark->CurDirection);
	std::cout << std::endl << std::endl;

	for (int row = 0; row < MAX_MOVE_DIRECTIONS; ++row)
	{
		std::cout << "pref dir: ";
		PrintDirection(row);
		std::cout << std::endl;

		for (int col = 0; col < MAX_MOVE_DIRECTIONS; ++col)
		{
			PrintDirection(shark->PreferDirections[row][col]);
			std::cout << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

int main()
{
	std::cin >> sMapSize >> sSharksSize >> sTotalScentCount;

	//std::unordered_map<int, Shark*> aliveSharks;
	//aliveSharks.reserve(sSharksSize * 2);

	for (int row = 0; row < sMapSize; ++row)
	{
		for (int col = 0; col < sMapSize; ++col)
		{
			int element;
			std::cin >> element;
			if (element > 0)
			{
				SharkInfo sharkInfo;
				sharkInfo.Id = element - 1;
				sharkInfo.CurPosition = { row, col };
				//aliveSharks.insert(std::pair<int, Shark*>(element, new Shark(position)));

				sSharkInfos[sharkInfo.Id] = sharkInfo;
			}

			sMap[row][col].SharkId = -1;
			sMap[row][col].ScentId = -1;
			sMap[row][col].Count = 0;
		}
	}
	
	for (unsigned int i = 0; i < sSharksSize; ++i)
	{
		unsigned int curDirection;
		std::cin >> curDirection;

		sSharkInfos[i].StartDirection = curDirection - 1;
	}

	std::queue<Shark*> aliveSharks;
	for (unsigned int i = 0; i < sSharksSize; ++i)
	{
		Shark* shark = new Shark(sSharkInfos[i].Id, sSharkInfos[i].CurPosition, sSharkInfos[i].StartDirection);

		for (int row = 0; row < MAX_MOVE_DIRECTIONS; ++row)
		{
			for (int col = 0; col < MAX_MOVE_DIRECTIONS; ++col)
			{
				unsigned int preferDirection;
				std::cin >> preferDirection;

				shark->PreferDirections[row][col] = preferDirection - 1;
			}
		}

		//PrintShark(shark);
		sMap[shark->CurPosition.Row][shark->CurPosition.Col].ScentId = shark->Id;
		sMap[shark->CurPosition.Row][shark->CurPosition.Col].Count = sTotalScentCount;

		aliveSharks.push(shark);
	}

	// Start game
	unsigned int time = 0;
	while (time <= MAX_TIME)
	{
		//std::cout << "time: " << time << std::endl;

		if (aliveSharks.size() == 1)
		{
			break;
		}

		unsigned int aliveSharksSize = aliveSharks.size();
		for (unsigned int i = 0; i < aliveSharksSize; ++i)
		{
			Shark* curShark = aliveSharks.front();
			aliveSharks.pop();

			int curRow = curShark->CurPosition.Row;
			int curCol = curShark->CurPosition.Col;

			// Todo: 모든 향을 먼저 뿌린 후, 움직어여야 함
			//sMap[curRow][curCol].ScentId = curShark->Id;
			//sMap[curRow][curCol].Count = sTotalScentCount;

			// Move
			unsigned int moveRow;
			unsigned int moveCol;
			unsigned int moveDir;

			for (unsigned int preferIndex = 0; preferIndex < MAX_MOVE_DIRECTIONS; ++preferIndex)
			{
				moveDir = curShark->PreferDirections[curShark->CurDirection][preferIndex];

				moveRow = curRow + sMoveDirections[moveDir].Row;
				moveCol = curCol + sMoveDirections[moveDir].Col;

				if (moveRow < 0 || moveRow >= sMapSize || moveCol < 0 || moveCol >= sMapSize)
				{
					continue;
				}

				//assert(moveRow >= 0 && moveRow < MAX_MAP_SIZE);
				//assert(moveCol >= 0 && moveCol < MAX_MAP_SIZE);

				if (sMap[moveRow][moveCol].Count <= 0)
				{
					goto move_block_found;
				}
			}

			for (unsigned int preferIndex = 0; preferIndex < MAX_MOVE_DIRECTIONS; ++preferIndex)
			{
				moveDir = curShark->PreferDirections[curShark->CurDirection][preferIndex];

				moveRow = curRow + sMoveDirections[moveDir].Row;
				moveCol = curCol + sMoveDirections[moveDir].Col;

				if (moveRow < 0 || moveRow >= sMapSize || moveCol < 0 || moveCol >= sMapSize)
				{
					continue;
				}

				//assert(moveRow >= 0 && moveRow < MAX_MAP_SIZE);
				//assert(moveCol >= 0 && moveCol < MAX_MAP_SIZE);

				if (sMap[moveRow][moveCol].ScentId == curShark->Id)
				{
					break;
				}
			}

			// always finds move block;

		move_block_found:

			assert(moveRow >= 0 && moveRow < MAX_MAP_SIZE);
			assert(moveCol >= 0 && moveCol < MAX_MAP_SIZE);

			/*
			std::cout << "move: ";
			PrintDirection(moveDir);
			std::cout << std::endl;
			*/

			sMap[curRow][curCol].SharkId = -1;
			if (sMap[moveRow][moveCol].SharkId != -1 && curShark->Id > sMap[moveRow][moveCol].SharkId)
			{
				delete curShark;

				continue;
			}

			sMap[moveRow][moveCol].SharkId = curShark->Id;

			curShark->CurPosition.Row = moveRow;
			curShark->CurPosition.Col = moveCol;
			curShark->CurDirection = moveDir;

			aliveSharks.push(curShark);

			//PrintShark(curShark);
		}

		// vanish scents
		for (int row = 0; row < sMapSize; ++row)
		{
			for (int col = 0; col < sMapSize; ++col)
			{
				if (sMap[row][col].Count > 0)
				{
					--(sMap[row][col].Count);
					
					if (sMap[row][col].Count == 0)
					{
						sMap[row][col].ScentId = -1;
					}
				}
			}
		}

		aliveSharksSize = aliveSharks.size();
		for (unsigned int i = 0; i < aliveSharksSize; ++i)
		{
			Shark* shark = aliveSharks.front();
			aliveSharks.pop();

			sMap[shark->CurPosition.Row][shark->CurPosition.Col].ScentId = shark->Id;
			sMap[shark->CurPosition.Row][shark->CurPosition.Col].Count = sTotalScentCount;

			aliveSharks.push(shark);
		}

		++time;

		//PrintMap();
		//std::cout << "alive: " << aliveSharks.size() << std::endl << std::endl;
	}
	
	while (aliveSharks.empty() == false)
	{
		Shark* delShark = aliveSharks.front();
		aliveSharks.pop();

		delete delShark;
	}

	if (time > MAX_TIME)
	{
		std::cout << -1 << std::endl;

		return 0;
	}

	std::cout << time << std::endl;

	return 0;
}


