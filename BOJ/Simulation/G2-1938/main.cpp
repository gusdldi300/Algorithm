
#include <cassert>
#include <iostream>
#include <cstdio>
#include <string.h>
#include <queue>

#define LOG_SIZE (3)
#define MAX_MAP_SIZE (51)

#define CENTER_POSITION_INDEX (1)
#define FIRST_POSITION_INDEX (0)
#define LAST_POSITION_INDEX (2)

#define MAX_MOVE_COUNT (4)
#define MAX_TURN_OFFSET_COUNT (8)

enum class eMove : unsigned int
{
	Up = 0x00,
	Down,
	Left,
	Right,
	Turn
};

enum class eOrientation : unsigned int
{
	Vertical = 0x00,
	Horizontal,
	Count
};

struct Position
{
	int Row;
	int Col;
};

struct Log
{
	Position Positions[LOG_SIZE];
	eOrientation Orientation;
};

void PrintMap(const unsigned int map[][MAX_MAP_SIZE], unsigned int mapSize)
{
	printf("Map\n");

	for (unsigned int row = 0; row < mapSize; ++row)
	{
		for (unsigned int col = 0; col < mapSize; ++col)
		{
			printf("%u", map[row][col]);
		}

		printf("\n");
	}

	printf("\n");
}

eOrientation getLogOrientation(const Position& firstPosition, const Position& centerPosition)
{
	if (firstPosition.Row == centerPosition.Row)
	{
		return eOrientation::Horizontal;
	}

	return eOrientation::Vertical;
}

bool IsPlaceable(int nextRow, int nextCol, unsigned int map[][MAX_MAP_SIZE], int mapSize)
{
	if (nextRow < 0 || nextRow >= mapSize || nextCol < 0 || nextCol >= mapSize)
	{
		return false;
	}

	if (map[nextRow][nextCol] == 1)
	{
		return false;
	}
	
	return true;
}

int main()
{
	int mapSize;
	std::cin >> mapSize;

	assert((mapSize >= 4) && (mapSize <= MAX_MAP_SIZE));

	unsigned int map[MAX_MAP_SIZE][MAX_MAP_SIZE];
	memset(map, 0, sizeof(unsigned int) * MAX_MAP_SIZE * MAX_MAP_SIZE);
	
	Log log;
	Log destination;

	unsigned int logIndex = 0;
	unsigned int destinationIndex = 0;
	
	std::string inputString;
	for (int row = 0; row < mapSize; ++row)
	{
		std::cin >> inputString;
		//assert(inputString.size() == mapSize);

		for (int col = 0; col < mapSize; ++col)
		{
			char currentSource = inputString[col];

			if (currentSource == 'B') {
				log.Positions[logIndex].Row = row;
				log.Positions[logIndex].Col = col;
				
				++logIndex;
			}
			else if (currentSource == 'E') {
				destination.Positions[destinationIndex].Row = row;
				destination.Positions[destinationIndex].Col = col;

				++destinationIndex;
			}
			else 
			{
				map[row][col] = currentSource - '0';
			}
		}
	}

	log.Orientation = getLogOrientation(log.Positions[FIRST_POSITION_INDEX], log.Positions[CENTER_POSITION_INDEX]);
	destination.Orientation = getLogOrientation(destination.Positions[FIRST_POSITION_INDEX], destination.Positions[CENTER_POSITION_INDEX]);

	//PrintMap(map, mapSize);

	const Position logNextPositionOffsets[MAX_MOVE_COUNT] = {
		{ -1, 0 },
		{ 1, 0 },
		{ 0, -1 },
		{ 0, 1 }
	};

	const Position logNextTurnOffsets[MAX_TURN_OFFSET_COUNT] = {
		{ -1, -1 },
		{ -1, 0 },
		{ -1, 1 },
		{ 0, 1 },
		{ 1, 1 },
		{ 1, 0 },
		{ 1, -1 },
		{ 0, -1 }
	};

	constexpr unsigned int ORIENTATION_COUNT = static_cast<unsigned int>(eOrientation::Count);
	bool visited[ORIENTATION_COUNT][MAX_MAP_SIZE][MAX_MAP_SIZE];
	memset(visited, 0, sizeof(bool) * ORIENTATION_COUNT * MAX_MAP_SIZE * MAX_MAP_SIZE);

	unsigned int turn = 0;
	bool bArrived = false;

	std::queue<Log> logQueue;
	logQueue.push(log);

	visited[static_cast<unsigned int>(log.Orientation)][log.Positions[CENTER_POSITION_INDEX].Row][log.Positions[CENTER_POSITION_INDEX].Col] = true;

	while (logQueue.empty() == false)
	{	
		unsigned int queueSize = logQueue.size();
		for (unsigned int queueIndex = 0; queueIndex < queueSize; ++queueIndex)
		{
			Log currentLog = logQueue.front();
			logQueue.pop();

			if ((currentLog.Positions[CENTER_POSITION_INDEX].Row == destination.Positions[CENTER_POSITION_INDEX].Row) &&
				(currentLog.Positions[CENTER_POSITION_INDEX].Col == destination.Positions[CENTER_POSITION_INDEX].Col) &&
				currentLog.Orientation == destination.Orientation)
			{
				bArrived = true;

				goto FOUND_LABEL;
			}

			for (unsigned int moveIndex = 0; moveIndex < (MAX_MOVE_COUNT + 1); ++moveIndex)
			{
				eMove move = static_cast<eMove>(moveIndex);
				bool bPlaceable = true;

				Log nextLog;
				nextLog.Orientation = currentLog.Orientation;

				if (move == eMove::Turn)
				{
					assert(moveIndex == MAX_MOVE_COUNT);

					for (unsigned int i = 0; i < MAX_TURN_OFFSET_COUNT; ++i)
					{
						int nextRow = currentLog.Positions[CENTER_POSITION_INDEX].Row + logNextTurnOffsets[i].Row;
						int nextCol = currentLog.Positions[CENTER_POSITION_INDEX].Col + logNextTurnOffsets[i].Col;

						bPlaceable = IsPlaceable(nextRow, nextCol, map, mapSize);
						if (bPlaceable == false)
						{
							break;
						}
					}

					assert(currentLog.Orientation != eOrientation::Count);

					nextLog.Positions[CENTER_POSITION_INDEX].Row = currentLog.Positions[CENTER_POSITION_INDEX].Row;
					nextLog.Positions[CENTER_POSITION_INDEX].Col = currentLog.Positions[CENTER_POSITION_INDEX].Col;

					if (currentLog.Orientation == eOrientation::Vertical)
					{
						nextLog.Positions[FIRST_POSITION_INDEX].Row = nextLog.Positions[CENTER_POSITION_INDEX].Row;
						nextLog.Positions[FIRST_POSITION_INDEX].Col = nextLog.Positions[CENTER_POSITION_INDEX].Col - 1;

						nextLog.Positions[LAST_POSITION_INDEX].Row = nextLog.Positions[CENTER_POSITION_INDEX].Row;
						nextLog.Positions[LAST_POSITION_INDEX].Col = nextLog.Positions[CENTER_POSITION_INDEX].Col + 1;

						nextLog.Orientation = eOrientation::Horizontal;
					}
					else
					{
						nextLog.Positions[FIRST_POSITION_INDEX].Row = nextLog.Positions[CENTER_POSITION_INDEX].Row - 1;
						nextLog.Positions[FIRST_POSITION_INDEX].Col = nextLog.Positions[CENTER_POSITION_INDEX].Col;

						nextLog.Positions[LAST_POSITION_INDEX].Row = nextLog.Positions[CENTER_POSITION_INDEX].Row + 1;
						nextLog.Positions[LAST_POSITION_INDEX].Col = nextLog.Positions[CENTER_POSITION_INDEX].Col;

						nextLog.Orientation = eOrientation::Vertical;
					}
				}
				else
				{
					assert(moveIndex < MAX_MOVE_COUNT);

					for (unsigned int logPositionIndex = 0; logPositionIndex < LOG_SIZE; ++logPositionIndex)
					{
						nextLog.Positions[logPositionIndex].Row = currentLog.Positions[logPositionIndex].Row + logNextPositionOffsets[moveIndex].Row;
						nextLog.Positions[logPositionIndex].Col = currentLog.Positions[logPositionIndex].Col + logNextPositionOffsets[moveIndex].Col;

						bPlaceable = IsPlaceable(nextLog.Positions[logPositionIndex].Row, nextLog.Positions[logPositionIndex].Col, map, mapSize);
						if (bPlaceable == false)
						{
							break;
						}
					}
				}

				if (bPlaceable == false)
				{
					continue;
				}

				unsigned int orientationIndex = static_cast<unsigned int>(nextLog.Orientation);
				if (visited[orientationIndex][nextLog.Positions[CENTER_POSITION_INDEX].Row][nextLog.Positions[CENTER_POSITION_INDEX].Col])
				{
					continue;
				}

				logQueue.push(nextLog);
				visited[orientationIndex][nextLog.Positions[CENTER_POSITION_INDEX].Row][nextLog.Positions[CENTER_POSITION_INDEX].Col] = true;
			}
		}

		++turn;
	}

FOUND_LABEL:

	if (bArrived) 
	{
		printf("%u", turn);
	}
	else
	{
		printf("0");
	}

	return 0;
}