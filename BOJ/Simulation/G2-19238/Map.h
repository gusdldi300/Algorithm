#pragma once

#include "Position.h"
#include "eElement.h"

class Map
{
public:
	Map(unsigned int mapSize, unsigned int passengersTotalCount);
	~Map();

	unsigned int GetPassengersTotalCount() const;
	unsigned int GetMapSize() const;
	int GetElement(int row, int col) const;

	void SetElement(const Position& position, int element);
	void Print() const;

public:
	enum { PERSON_START_ID = 2 };

private:
	unsigned int mPassengersTotalCount;
	unsigned int mMapSize;
	int** mMap;
};