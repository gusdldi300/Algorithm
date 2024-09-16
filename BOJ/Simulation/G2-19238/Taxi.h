#pragma once

#include <vector>

#include "Position.h"
#include "Map.h";
#include "Person.h";

class Taxi
{
public:
	Taxi(const Position& position, unsigned int fuelAmount);
	~Taxi() = default;

	const Position& GetPosition() const;
	int GetAllPassengersToDestination(Map* map, const std::vector<Person>& passengers);

private:
	void resetVisited(bool** visited, unsigned int size) const;

private:
	enum { DIRECTIONS_SIZE = 4 };
	Position mDirections[DIRECTIONS_SIZE] =
	{
		Position(-1, 0),
		Position(0, 1),
		Position(1, 0),
		Position(0, -1)
	};

	Position mPosition;
	unsigned int mFuelAmount;
};