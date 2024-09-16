
#include <queue>
#include <iostream>

#include "Taxi.h"
#include "Map.h"
#include "Person.h"

Taxi::Taxi(const Position& position, unsigned int fuelAmount)
	: mPosition(position)
	, mFuelAmount(fuelAmount)
{
}

const Position& Taxi::GetPosition() const
{
	return mPosition;
}

int Taxi::GetAllPassengersToDestination(Map* map, const std::vector<Person>& passengers)
{
	unsigned int mapSize = map->GetMapSize();

	bool** visited = new bool* [mapSize];
	for (unsigned int row = 0; row < mapSize; ++row)
	{
		visited[row] = new bool[mapSize];
	}

	unsigned int curPassengersCount = 0;
	while (curPassengersCount < map->GetPassengersTotalCount())
	{
		resetVisited(visited, mapSize);

		std::queue<Position> positions;
		positions.push(mPosition);
		visited[mPosition.GetRow()][mPosition.GetCol()];

		std::queue<unsigned int> equalDistancePassengerIds;

		unsigned int moveDistance = 0;

		while (positions.empty() == false)
		{
			unsigned int curDistanceSize = positions.size();
			for (unsigned int i = 0; i < curDistanceSize; ++i)
			{
				Position curPosition = positions.front();
				positions.pop();

				int mapElement = map->GetElement(curPosition.GetRow(), curPosition.GetCol());
				if (mapElement >= Map::PERSON_START_ID)
				{
					//std::cout << "Found passenger: " << mapElement << std::endl;
					equalDistancePassengerIds.push(mapElement);
				}

				for (unsigned int dirIndex = 0; dirIndex < DIRECTIONS_SIZE; ++dirIndex)
				{
					int nextRow = curPosition.GetRow() + mDirections[dirIndex].GetRow();
					int nextCol = curPosition.GetCol() + mDirections[dirIndex].GetCol();

					if (nextRow < 0 || nextRow >= mapSize || nextCol < 0 || nextCol >= mapSize)
					{
						continue;
					}

					if (visited[nextRow][nextCol] || map->GetElement(nextRow, nextCol) == 1)
					{
						continue;
					}

					positions.push(Position(nextRow, nextCol));
					visited[nextRow][nextCol] = true;
				}
			}

			if (equalDistancePassengerIds.empty() == false)
			{
				break;
			}

			++moveDistance;
		}

		if (moveDistance > mFuelAmount || equalDistancePassengerIds.empty())
		{
			return -1;
		}
		mFuelAmount -= moveDistance;

		int foundPassengerId = equalDistancePassengerIds.front();
		equalDistancePassengerIds.pop();

		Person foundPassenger = passengers[foundPassengerId - Map::PERSON_START_ID];
		while (equalDistancePassengerIds.empty() == false)
		{
			int curPassengerId = equalDistancePassengerIds.front();
			equalDistancePassengerIds.pop();

			Person curPassenger = passengers[curPassengerId - Map::PERSON_START_ID];
			if (curPassenger.GetStart().GetRow() < foundPassenger.GetStart().GetRow())
			{
				foundPassengerId = curPassengerId;
				foundPassenger = curPassenger;
			}
			else if (curPassenger.GetStart().GetRow() == foundPassenger.GetStart().GetRow())
			{
				if (curPassenger.GetStart().GetCol() < foundPassenger.GetStart().GetCol())
				{
					foundPassengerId = curPassengerId;
					foundPassenger = curPassenger;
				}
			}
		}

		mPosition = foundPassenger.GetStart();
		map->SetElement(mPosition, 0);

		// Go to destination
		positions = std::queue<Position>();
		positions.push(mPosition);

		resetVisited(visited, mapSize);

		moveDistance = 0;
		bool bFoundDestination = false;
		while (positions.empty() == false)
		{
			unsigned int curDistanceSize = positions.size();

			for (unsigned int i = 0; i < curDistanceSize; ++i)
			{
				Position curPosition = positions.front();
				positions.pop();

				if (curPosition == foundPassenger.GetDestination())
				{
					//std::cout << "Found destination: " << mapElement << std::endl;
					bFoundDestination = true;
					goto outer;
				}

				for (unsigned int dirIndex = 0; dirIndex < DIRECTIONS_SIZE; ++dirIndex)
				{
					int nextRow = curPosition.GetRow() + mDirections[dirIndex].GetRow();
					int nextCol = curPosition.GetCol() + mDirections[dirIndex].GetCol();

					if (nextRow < 0 || nextRow >= mapSize || nextCol < 0 || nextCol >= mapSize)
					{
						continue;
					}

					if (visited[nextRow][nextCol] || map->GetElement(nextRow, nextCol) == 1)
					{
						continue;
					}

					positions.push(Position(nextRow, nextCol));
					visited[nextRow][nextCol] = true;
				}
			}

			++moveDistance;
		}

	outer:
		if (bFoundDestination == false || moveDistance > mFuelAmount)
		{
			return -1;
		}
		mFuelAmount -= moveDistance;
		mFuelAmount += (moveDistance * 2);

		mPosition = foundPassenger.GetDestination();

		++curPassengersCount;

		//map->Print();
	}

	for (unsigned int row = 0; row < mapSize; ++row)
	{
		delete[] visited[row];
	}
	delete[] visited;

	return mFuelAmount;
}

void Taxi::resetVisited(bool** visited, unsigned int size) const
{
	for (unsigned int row = 0; row < size; ++row)
	{
		for (unsigned int col = 0; col < size; ++col)
		{
			visited[row][col] = false;
		}
	}
}