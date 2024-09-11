
#include <cassert>
#include <iostream>
#include <queue>
#include <limits>

#define DIRECTIONS_SIZE (4)

typedef struct
{
	int row;
	int col;
} position_t;

typedef struct
{
	unsigned int startIsland;
	position_t position;
	unsigned int dirIndex;
} block_t;

static position_t sDirections[] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } }; // clockwise

static void NumberIslandAndGetBridgeBlocks(position_t startPosition, std::queue<position_t>* positions, unsigned int islandNumber, unsigned int** outMap, bool** outVisited, const position_t* mapSize, std::queue<block_t>* outBridgeBlocks)
{
	assert(outMap != nullptr);
	assert(outVisited != nullptr);

	positions->push(startPosition);

	outMap[startPosition.row][startPosition.col] = islandNumber;
	outVisited[startPosition.row][startPosition.col] = true;

	while (!positions->empty())
	{
		position_t position = positions->front();
		positions->pop();
			
		for (unsigned int dirIndex = 0; dirIndex < DIRECTIONS_SIZE; ++dirIndex)
		{
			int nextRow = position.row + sDirections[dirIndex].row;
			int nextCol = position.col + sDirections[dirIndex].col;

			if (nextRow < 0 || nextRow >= mapSize->row || nextCol < 0 || nextCol >= mapSize->col)
			{
				continue;
			}

			if (outVisited[nextRow][nextCol])
			{
				continue;
			}

			position_t nextPosition = { nextRow, nextCol };

			if (outMap[nextRow][nextCol] == 0)
			{
				block_t bridegTestBlock{ islandNumber, nextPosition, dirIndex };
				outBridgeBlocks->push(bridegTestBlock);

				continue;
			}

			outMap[nextRow][nextCol] = islandNumber;
			outVisited[nextRow][nextCol] = true;

			positions->push(nextPosition);
		}
	}
}

unsigned int ClassifyIslands(unsigned int** outMap, const position_t* mapSize, std::queue<block_t>* outBridegBlocks)
{
	assert(outMap != nullptr);

	bool** visited = new bool*[mapSize->row];
	for (int row = 0; row < mapSize->row; ++row)
	{
		visited[row] = new bool[mapSize->col];
	}

	for (int row = 0; row < mapSize->row; ++row)
	{
		for (int col = 0; col < mapSize->col; ++col)
		{
			visited[row][col] = false;
		}
	}

	std::queue<position_t> positions;
	unsigned int islandNumber = 1;
	for (int row = 0; row < mapSize->row; ++row)
	{
		for (int col = 0; col < mapSize->col; ++col)
		{
			if (visited[row][col] || outMap[row][col] == 0)
			{
				continue;
			}

			position_t startPosition = { row, col };
			NumberIslandAndGetBridgeBlocks(startPosition, &positions, islandNumber, outMap, visited, mapSize, outBridegBlocks);
			
			islandNumber++;
		}
	}

	for (int row = 0; row < mapSize->row; ++row)
	{
		delete visited[row];
	}
	delete[] visited;

	return islandNumber - 1;
}

static void PrintMap(unsigned int** map, unsigned int rowSize, unsigned int colSize)
{
	std::cout << "Map" << std::endl;

	for (unsigned int row = 0; row < rowSize; ++row)
	{
		for (unsigned int col = 0; col < colSize; ++col)
		{
			std::cout << map[row][col] << " ";
		}
		
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

static void PrintBridgesBlockCount(unsigned int** bridge, unsigned int rowSize, unsigned int colSize)
{
	for (unsigned int row = 0; row < rowSize; ++row)
	{
		for (unsigned int col = 0; col < colSize; ++col)
		{
			if (bridge[row][col] == UINT32_MAX)
			{
				std::cout << 0 << " ";
			}
			else 
			{
				std::cout << bridge[row][col] << " ";
			}
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

static void traverseVisitedIslandRecursive(const std::vector<unsigned int>* islandsConnected, unsigned int curIslandIndex, bool* bVisited)
{
	std::vector<unsigned int> curIsland = islandsConnected[curIslandIndex];
	for (unsigned int island : curIsland)
	{
		if (bVisited[island] == false)
		{
			bVisited[island] = true;
			traverseVisitedIslandRecursive(islandsConnected, island, bVisited);
		}
	}
}

static void getTotalBlockCountRecursive(unsigned int* outMinBlockCount, unsigned int curIndex, unsigned int** bridgeBlockCounts, const unsigned int islandCount, unsigned int curBridgeCount, position_t* selectedBridges, const unsigned int bridgeCount, std::vector<unsigned int>* islandsConnected)
{
	if (curBridgeCount == bridgeCount)
	{
		assert(islandCount > 2);
		
		bool* bVisited = new bool[islandCount];
		for (unsigned int i = 0; i < islandCount; ++i)
		{
			bVisited[i] = false;
		}
		
		bVisited[1] = true;
		traverseVisitedIslandRecursive(islandsConnected, 1, bVisited);

		unsigned int curBlockCount = 0;
		for (unsigned int i = 1; i < islandCount; ++i)
		{
			if (bVisited[i] == false)
			{
				goto complete;
			}
		}

		for (unsigned int i = 0; i < bridgeCount; ++i)
		{
			curBlockCount += bridgeBlockCounts[selectedBridges[i].row][selectedBridges[i].col];
		}

		if (curBlockCount < *outMinBlockCount)
		{
			//printf("cur block count: %d\n", curBlockCount);
			*outMinBlockCount = curBlockCount;
		}

	complete:
		delete[] bVisited;

		return;
	}
	
	unsigned int nextIndex = curIndex;
	for (int row = (nextIndex / islandCount); row < islandCount; ++row)
	{
		for (int col = (nextIndex % islandCount); col < islandCount; ++col)
		{
			++nextIndex;
			if (col <= row || bridgeBlockCounts[row][col] == UINT32_MAX)
			{
				continue;
			}

			selectedBridges[curBridgeCount].row = row;
			selectedBridges[curBridgeCount].col = col;

			islandsConnected[row].push_back(col);
			islandsConnected[col].push_back(row);

			getTotalBlockCountRecursive(outMinBlockCount, nextIndex, bridgeBlockCounts, islandCount, curBridgeCount + 1, selectedBridges, bridgeCount, islandsConnected);

			islandsConnected[row].pop_back();
			islandsConnected[col].pop_back();
		}
	}
}

int main()
{
	int rowSize;
	int colSize;
		
	std::cin >> rowSize >> colSize;
	
	unsigned int** map = new unsigned int*[rowSize];
	for (int row = 0; row < rowSize; ++row)
	{
		map[row] = new unsigned int[colSize];
	}
	
	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			std::cin >> map[row][col];

		}
	}

	//PrintMap(map, rowSize, colSize);

	const position_t mapSize = { rowSize, colSize };
	std::queue<block_t> bridgeTestBlocks;
	unsigned int islandCount = ClassifyIslands(map, &mapSize, &bridgeTestBlocks) + 1;

	unsigned int** bridgeBlockCounts = new unsigned int* [islandCount];
	for (int row = 0; row < islandCount; ++row)
	{
		bridgeBlockCounts[row] = new unsigned int[islandCount];
	}

	for (int row = 0; row < islandCount; ++row)
	{
		for (int col = 0; col < islandCount; ++col)
		{
			bridgeBlockCounts[row][col] = UINT32_MAX;
		}
	}

	//PrintMap(map, rowSize, colSize);
	// get min bridge block count
	{
		while (!bridgeTestBlocks.empty())
		{
			block_t bridgeStartBlock = bridgeTestBlocks.front();
			bridgeTestBlocks.pop();

			int nextRow = bridgeStartBlock.position.row;
			int nextCol = bridgeStartBlock.position.col;

			unsigned int blockCount = 1;
			unsigned int foundIslandNumber = 0;
			while (true)
			{
				nextRow += sDirections[bridgeStartBlock.dirIndex].row;
				nextCol += sDirections[bridgeStartBlock.dirIndex].col;

				if (nextRow < 0 || nextRow >= mapSize.row || nextCol < 0 || nextCol >= mapSize.col)
				{
					break;
				}
				
				if (map[nextRow][nextCol] > 0)
				{
					if (blockCount > 1) {
						foundIslandNumber = map[nextRow][nextCol];
					}

					break;
				}

				++blockCount;
			}
			
			if (foundIslandNumber > 0 && foundIslandNumber != bridgeStartBlock.startIsland)
			{
				if (blockCount < bridgeBlockCounts[bridgeStartBlock.startIsland][foundIslandNumber])
				{
					bridgeBlockCounts[bridgeStartBlock.startIsland][foundIslandNumber] = blockCount;
					bridgeBlockCounts[foundIslandNumber][bridgeStartBlock.startIsland] = blockCount;
				}
			}
		}
	}

	//PrintBridgesBlockCount(bridgeBlockCounts, islandCount, islandCount);

	unsigned int minTotalBlockCount = UINT32_MAX;
	// get min bridge counts using combination
	if (islandCount > 2)
	{
		unsigned int minBridgeCount = islandCount - 2;
		position_t* selectedBridges = new position_t[minBridgeCount];

		std::vector<unsigned int>* islandsConnected = new std::vector<unsigned int>[islandCount];
		getTotalBlockCountRecursive(&minTotalBlockCount, 0, bridgeBlockCounts, islandCount, 0, selectedBridges, minBridgeCount, islandsConnected);

		delete[] selectedBridges;
	}

	if (minTotalBlockCount == UINT32_MAX) 
	{
		std::cout << -1;
	}
	else {
		std::cout << minTotalBlockCount;
	}

	for (int row = 0; row < islandCount; ++row)
	{
		delete[] bridgeBlockCounts[row];
	}

	delete[] bridgeBlockCounts;

	for (int row = 0; row < rowSize; ++row)
	{
		delete[] map[row];
	}

	delete[] map;

	return 0;
}
