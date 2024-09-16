
#include <cassert>
#include <iostream>

#include "Map.h"
#include "Taxi.h"
#include "Person.h"
#include "Position.h"

int main()
{
	unsigned int mapSize;
	unsigned int passengersTotalCount;
	unsigned int initFuelAmount;

	std::cin >> mapSize >> passengersTotalCount >> initFuelAmount;
	Map map(mapSize, passengersTotalCount);

	for (unsigned int row = 0; row < mapSize; ++row)
	{
		for (unsigned int col = 0; col < mapSize; ++col)
		{
			unsigned int element;
			std::cin >> element;

			Position position(row, col);
			map.SetElement(position, element);
		}
	}

	unsigned int startRow;
	unsigned int startCol;
	std::cin >> startRow >> startCol;

	Taxi taxi(Position(startRow - 1, startCol - 1), initFuelAmount);

	std::vector<Person> passengers;
	passengers.reserve(passengersTotalCount);

	int personId = Map::PERSON_START_ID;
	for (unsigned int i = 0; i < passengersTotalCount; ++i)
	{
		unsigned int personStartRow;
		unsigned int personStartCol;

		unsigned int personDestRow;
		unsigned int personDestCol;

		std::cin >> personStartRow >> personStartCol >> personDestRow >> personDestCol;

		Position startPosition(personStartRow - 1, personStartCol - 1);
		Position destPosition(personDestRow - 1, personDestCol - 1);
		passengers.push_back(Person(startPosition, destPosition));

		map.SetElement(startPosition, personId);

		++personId;
	}

	//map.Print();

	int leftFuelAmount = taxi.GetAllPassengersToDestination(&map, passengers);
	std::cout << leftFuelAmount << std::endl;

	return 0;
}