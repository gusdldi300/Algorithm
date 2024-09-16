
#include "Map.h"
#include <iostream>
#include <cassert>


Map::Map(unsigned int mapSize, unsigned int passengersTotalCount)
	: mMapSize(mapSize)
	, mPassengersTotalCount(passengersTotalCount)
{
	mMap = new int* [mapSize];
	for (int row = 0; row < mapSize; ++row)
	{
		mMap[row] = new int[mapSize];
	}
}

Map::~Map()
{
	for (int row = 0; row < mMapSize; ++row)
	{
		delete[] mMap[row];
	}
	delete[] mMap;
}

unsigned int Map::GetPassengersTotalCount() const
{
	return mPassengersTotalCount;
}

unsigned int Map::GetMapSize() const
{
	return mMapSize;
}

int Map::GetElement(int row, int col) const
{
	assert((row >= 0 && row < mMapSize) && (col >= 0 && col < mMapSize));

	return mMap[row][col];
}

void Map::SetElement(const Position& position, int element)
{
	mMap[position.GetRow()][position.GetCol()] = element;
}

void Map::Print() const
{
	std::cout << "Map" << std::endl;

	for (unsigned int row = 0; row < mMapSize; ++row)
	{
		for (unsigned int col = 0; col < mMapSize; ++col)
		{
			std::cout << static_cast<int>(mMap[row][col]) << ' ';
		}

		std::cout << std::endl;
	}
}