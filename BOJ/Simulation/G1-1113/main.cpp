#include <limits>
#include <iostream>
#include <queue>

#define MAX_HEIGHT (9)

#define MAX_ROW_SIZE (50)
#define MAX_COL_SIZE (50)

#define MAX_DIRECTIONS_SIZE (4)

typedef struct
{
	int Row;
	int Col;
} Position;

static unsigned int sPool[MAX_ROW_SIZE][MAX_COL_SIZE];
static unsigned int sRowSize;
static unsigned int sColSize;

static Position sMoveDirections[] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static void PrintPool()
{
	std::cout << "Pool" << std::endl;

	for (unsigned int row = 0; row < sRowSize; ++row)
	{
		for (unsigned int col = 0; col < sColSize; ++col)
		{
			std::cout << sPool[row][col] << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

static unsigned int addWaterOnTiles(int row, int col, unsigned int height)
{
	bool visited[MAX_ROW_SIZE][MAX_COL_SIZE] = { false, };

	bool bOutOfPool = false;
	unsigned int minWallHeight = std::numeric_limits<unsigned int>::max();

	std::queue<Position> positionQueue;
	positionQueue.push({ row, col });
	visited[row][col] = true;

	while (positionQueue.empty() == false)
	{
		Position position = positionQueue.front();
		positionQueue.pop();

		for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_SIZE; ++dirIndex)
		{
			int nextRow = position.Row + sMoveDirections[dirIndex].Row;
			int nextCol = position.Col + sMoveDirections[dirIndex].Col;

			if ((nextRow < 0 || nextRow >= sRowSize || nextCol < 0 || nextCol >= sColSize) || (sPool[nextRow][nextCol] > MAX_HEIGHT))
			{
				bOutOfPool = true;
				
				continue;
			}

			if (visited[nextRow][nextCol])
			{
				continue;
			}

			if (sPool[row][col] < sPool[nextRow][nextCol])
			{
				if (sPool[nextRow][nextCol] < minWallHeight)
				{
					minWallHeight = sPool[nextRow][nextCol];
				}
				
				continue;
			}

			visited[nextRow][nextCol] = true;
			positionQueue.push({ nextRow, nextCol });
		}
	}

	unsigned int addedWater = 0;

	for (unsigned int row = 0; row < sRowSize; ++row)
	{
		for (unsigned int col = 0; col < sColSize; ++col)
		{
			if (visited[row][col] == false)
			{
				continue;
			}

			if (bOutOfPool)
			{
				sPool[row][col] = MAX_HEIGHT + 1;
			}
			else
			{
				addedWater += (minWallHeight - sPool[row][col]);
				sPool[row][col] = minWallHeight;
			}
		}
	}

	/*
	unsigned int addedWater = 0;
	
	positionQueue.push({ row, col });
	visited[row][col] = true;

	while (positionQueue.empty() == false)
	{
		Position position = positionQueue.front();
		positionQueue.pop();

		if (bOutOfPool)
		{
			sPool[position.Row][position.Col] = MAX_HEIGHT + 1;
		}
		else
		{
			addedWater += (minWallHeight - sPool[position.Row][position.Col]);
			sPool[position.Row][position.Col] = minWallHeight;
		}

		for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_SIZE; ++dirIndex)
		{
			int nextRow = position.Row + sMoveDirections[dirIndex].Row;
			int nextCol = position.Col + sMoveDirections[dirIndex].Col;

			if ((nextRow < 0 || nextRow >= sRowSize || nextCol < 0 || nextCol >= sColSize) || (sPool[nextRow][nextCol] > MAX_HEIGHT))
			{
				continue;
			}

			if (visited[nextRow][nextCol] || sPool[nextRow][nextCol] > height)
			{
				continue;
			}

			visited[nextRow][nextCol] = true;
			positionQueue.push({ nextRow, nextCol });
		}
	}

	*/

	return addedWater;
}

int main()
{

	std::cin >> sRowSize >> sColSize;
	std::string heights;

	for (int row = 0; row < sRowSize; ++row)
	{
		std::cin >> heights;
		
		for (int col = 0; col < sColSize; ++col)
		{
			sPool[row][col] = (heights[col] - '0');
		}
	}

	//PrintPool();
	unsigned int totalAddedWater = 0;

	for (unsigned int height = 1; height <= MAX_HEIGHT; ++height)
	{
		unsigned int curAddedWater = 0;
		for (int row = 0; row < sRowSize; ++row)
		{
			for (int col = 0; col < sColSize; ++col)
			{
				if (sPool[row][col] != height)
				{
					continue;
				}

				curAddedWater = addWaterOnTiles(row, col, height);
				totalAddedWater += curAddedWater;
			}
		}

		std::cout << "height: " << height << std::endl;
		std::cout << "total water: " << totalAddedWater << std::endl;
		PrintPool();
	}
	
	std::cout << totalAddedWater << std::endl;

	return 0;
}