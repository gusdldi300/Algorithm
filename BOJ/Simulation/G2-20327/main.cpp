#include <iostream>
#include <cassert>
#include <cmath>

#define MAX_MAP_SIZE (128)
#define MAX_OPERATIONS_SIZE (1000)

typedef struct
{
	unsigned int Id;
	unsigned int Length;
} Operation;

static unsigned int sMapSizeExponent;
static int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
static int sTransformedMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

static unsigned int sOperationsCount;
//static Operation sOperations[MAX_OPERATIONS_SIZE];

static void PrintTransformedMap(unsigned int mapSize)
{
	//std::cout << "Transformed Map" << std::endl;

	for (unsigned int row = 0; row < mapSize; ++row)
	{
		for (unsigned int col = 0; col < mapSize; ++col)
		{
			std::cout << sTransformedMap[row][col] << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

static void ResetTransformedMap(unsigned int mapSize)
{
	for (unsigned int row = 0; row < mapSize; ++row)
	{
		for (unsigned int col = 0; col < mapSize; ++col)
		{
			sTransformedMap[row][col] = 0;
		}
	}
}

static void CopyTransformedMap(unsigned int mapSize)
{
	for (unsigned int row = 0; row < mapSize; ++row)
	{
		for (unsigned int col = 0; col < mapSize; ++col)
		{
			sMap[row][col] = sTransformedMap[row][col];
		}
	}
}

static void fillTransformedMap(unsigned int mapStartRow, unsigned int mapStartCol, unsigned int transformedMapStartRow, unsigned int transformedMapStartCol, unsigned int length)
{
	unsigned int mapRow = mapStartRow;
	unsigned int mapCol = mapStartCol;

	unsigned int transformedMapRow = transformedMapStartRow;
	unsigned int transformedMapCol = transformedMapStartCol;

	for (unsigned int i = 0; i < length; ++i)
	{
		mapCol = mapStartCol;
		transformedMapCol = transformedMapStartCol;

		for (unsigned int j = 0; j < length; ++j)
		{
			sTransformedMap[transformedMapRow][transformedMapCol] = sMap[mapRow][mapCol];

			++mapCol;
			++transformedMapCol;
		}

		++mapRow;
		++transformedMapRow;
	}
}

static void tryUpDownReversal(unsigned int startRow, unsigned int startCol, unsigned int mapSize, unsigned int blockSize)
{
	unsigned int count = mapSize / blockSize;

	unsigned int transformedRow = count - 1;
	for (unsigned int row = 0; row < count; ++row)
	{
		unsigned int blockStartRow = startRow + (blockSize * row);
		unsigned int otherBlockStartRow = startRow + (blockSize * transformedRow);

		for (unsigned int col = 0; col < count; ++col)
		{
			unsigned int blockStartCol = startCol + (blockSize * col);
			fillTransformedMap(blockStartRow, blockStartCol, otherBlockStartRow, blockStartCol, blockSize);
		}

		transformedRow--;
	}
}

static void tryLeftRightReversal(unsigned int startRow, unsigned int startCol, unsigned int mapSize, unsigned int blockSize)
{
	unsigned int count = mapSize / blockSize;

	unsigned int transformedCol = count - 1;
	for (unsigned int col = 0; col < count; ++col)
	{
		unsigned int blockStartCol = startCol + (blockSize * col);
		unsigned int otherBlockStartCol = startCol + (blockSize * transformedCol);

		for (unsigned int row = 0; row < count; ++row)
		{
			unsigned int blockStartRow = startRow + (blockSize * row);
			fillTransformedMap(blockStartRow, blockStartCol, blockStartRow, otherBlockStartCol, blockSize);
		}

		transformedCol--;
	}
}

static void rotateRight(unsigned int startRow, unsigned int startCol, unsigned int mapSize, unsigned int blockSize)
{
	unsigned int count = mapSize / blockSize;

	unsigned int transformedCol = count - 1;
	for (unsigned int row = 0; row < count; ++row)
	{
		unsigned int transformedRow = 0;

		unsigned int blockStartRow = startRow + (blockSize * row);
		unsigned int otherBlockStartCol = startCol + (blockSize * transformedCol);
		
		for (unsigned int col = 0; col < count; ++col)
		{
			unsigned int blockStartCol = startCol + (blockSize * col);
			unsigned int otherBlockStartRow = startRow + (blockSize * transformedRow);

			fillTransformedMap(blockStartRow, blockStartCol, otherBlockStartRow, otherBlockStartCol, blockSize);

			++transformedRow;
		}

		--transformedCol;
	}
}

static void rotateLeft(unsigned int startRow, unsigned int startCol, unsigned int mapSize, unsigned int blockSize)
{
	unsigned int count = mapSize / blockSize;

	unsigned int transformedCol = 0;
	for (unsigned int row = 0; row < count; ++row)
	{
		unsigned int transformedRow = count - 1;

		unsigned int blockStartRow = startRow + (blockSize * row);
		unsigned int otherBlockStartCol = startCol + (blockSize * transformedCol);

		for (unsigned int col = 0; col < count; ++col)
		{
			unsigned int blockStartCol = startCol + (blockSize * col);
			unsigned int otherBlockStartRow = startRow + (blockSize * transformedRow);

			fillTransformedMap(blockStartRow, blockStartCol, otherBlockStartRow, otherBlockStartCol, blockSize);

			--transformedRow;
		}

		++transformedCol;
	}
}

int main()
{
	std::cin >> sMapSizeExponent >> sOperationsCount;
	unsigned int mapSize = static_cast<unsigned int>(pow(2.0, sMapSizeExponent));

	for (unsigned int row = 0; row < mapSize; ++row)
	{
		for (unsigned int col = 0; col < mapSize; ++col)
		{
			std::cin >> sMap[row][col];
		}
	}

	for (unsigned int operationIndex = 0; operationIndex < sOperationsCount; ++operationIndex)
	{
		unsigned int curExponent;
		unsigned int curOperation;
		
		std::cin >> curOperation >> curExponent;

		unsigned int partialMapSize = static_cast<unsigned int>(pow(2.0, curExponent));
		unsigned int totalCount = mapSize / partialMapSize;

		//memset(sTransformedMap, 0, MAX_MAP_SIZE * MAX_MAP_SIZE);
		assert(curOperation > 0);

		if (curOperation < 5) 
		{
			for (unsigned int i = 0; i < totalCount; ++i)
			{
				unsigned int startRow = i * partialMapSize;
				for (unsigned int j = 0; j < totalCount; ++j)
				{
					unsigned int startCol = j * partialMapSize;
					
					switch (curOperation)
					{
					case 1:
						tryUpDownReversal(startRow, startCol, partialMapSize, 1);
						break;
					case 2:
						tryLeftRightReversal(startRow, startCol, partialMapSize, 1);
						break;
					case 3:
						rotateRight(startRow, startCol, partialMapSize, 1);
						break;
					case 4:
						rotateLeft(startRow, startCol, partialMapSize, 1);
						break;
					default:
						assert(false);
						break;
					}
				}
			}
		}
		else
		{
			switch (curOperation)
			{
			case 5:
				tryUpDownReversal(0, 0, mapSize, partialMapSize);
				break;
			case 6:
				tryLeftRightReversal(0, 0, mapSize, partialMapSize);
				break;
			case 7:
				rotateRight(0, 0, mapSize, partialMapSize);
				break;
			case 8:
				rotateLeft(0, 0, mapSize, partialMapSize);
				break;
			default:
				assert(false);
				break;
			}
		}

		//PrintTransformedMap(mapSize);

		CopyTransformedMap(mapSize);
		//ResetTransformedMap(mapSize);
	}

	PrintTransformedMap(mapSize);

	return 0;
}
