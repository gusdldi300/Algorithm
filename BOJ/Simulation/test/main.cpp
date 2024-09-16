#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class Position
{
public:
	Position(int row, int col);
	~Position() = default;

	Position(const Position& other) = default;
	Position& operator=(const Position& other) = default;

	bool operator==(const Position& other) const;

	int GetRow() const;
	int GetCol() const;

private:
	int mRow;
	int mCol;
};

Position::Position(int row, int col)
	: mRow(row)
	, mCol(col)
{
}

bool Position::operator==(const Position& other) const
{
	if (mRow == other.mRow && mCol == other.mCol)
	{
		return true;
	}

	return false;
}

int Position::GetRow() const
{
	return mRow;
}

int Position::GetCol() const
{
	return mCol;
}

class Person
{
public:
	Person(const Position& start, const Position& destination);
	~Person() = default;

	const Position& GetStart() const;
	const Position& GetDestination() const;

private:
	Position mStart;
	Position mDestination;
};

Person::Person(const Position& start, const Position& destination)
	: mStart(start)
	, mDestination(destination)
{
}

const Position& Person::GetStart() const
{
	return mStart;
}

const Position& Person::GetDestination() const
{
	return mDestination;
}


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

	bool** visited = new bool*[mapSize];
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