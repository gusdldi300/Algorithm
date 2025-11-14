#include <iostream>
#include <cassert>

#define MAX_INGREDIENTS_COUNT (10U)
#define MAX_INGREDIENTS_SIZE (4)

#define MAX_KILN_SIZE (5)

#define MAX_INGREDIENTS_ROTATE_CW_COUNT (4U)
#define MAX_INGREDIENTS_POSITION_COUNT (4U)

#define MAX_INSERT_INGREDIENTS_COUNT (3U)
#define MAX_QUALITIES_SIZE (5U)

enum class eRotationCW
{
	Degree0,
	Degree90,
	Degree180,
	Degree270,
};

enum class eColor : unsigned int
{
	White = 0,
	Red,
	Blue,
	Green,
	Yellow
};

struct Ingredient
{
	int Quality;
	eColor Color;
};

struct Position
{
	int Row;
	int Col;
};

static const Position INGREDIENTS_START_POSITION[MAX_INGREDIENTS_POSITION_COUNT] = { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 0 } };
static Ingredient sIngredients[MAX_INGREDIENTS_COUNT][MAX_INGREDIENTS_SIZE][MAX_INGREDIENTS_SIZE] = { 0, };

static int sBestQualityBomb = 0;

static void CopyKiln(Ingredient destination[][MAX_KILN_SIZE], const Ingredient source[][MAX_KILN_SIZE])
{
	for (int row = 0; row < MAX_KILN_SIZE; ++row)
	{
		for (int col = 0; col < MAX_KILN_SIZE; ++col)
		{
			destination[row][col] = source[row][col];
		}
	}
}

static void GetBestQualityBombRecursive(unsigned int ingredientsCount, const unsigned int maxIngredientsCount, const Ingredient kiln[][MAX_KILN_SIZE], bool visited[])
{
	if (ingredientsCount == MAX_INSERT_INGREDIENTS_COUNT)
	{
		// Todo: Check quality
		int qualities[MAX_QUALITIES_SIZE] = { 0, };

		for (int row = 0; row < MAX_KILN_SIZE; ++row)
		{
			for (int col = 0; col < MAX_KILN_SIZE; ++col)
			{
				if (kiln[row][col].Color == eColor::White)
				{
					continue;
				}

				qualities[static_cast<unsigned int>(kiln[row][col].Color)] += kiln[row][col].Quality;
			}
		}

		int bombQuality = (7 * qualities[1]) + (5 * qualities[2]) + (3 * qualities[3]) + (2 * qualities[4]);
		sBestQualityBomb = sBestQualityBomb < bombQuality ? bombQuality : sBestQualityBomb;

		return;
	}

	for (unsigned int ingredientsIndex = 0; ingredientsIndex < maxIngredientsCount; ++ingredientsIndex)
	{
		if (visited[ingredientsIndex])
		{
			continue;
		}

		visited[ingredientsIndex] = true;

		// Rotate
		for (unsigned int rotateIndex = 0; rotateIndex < MAX_INGREDIENTS_ROTATE_CW_COUNT; ++rotateIndex)
		{
			eRotationCW rotation = static_cast<eRotationCW>(rotateIndex);

			// Start position
			for (unsigned int startPositionIndex = 0; startPositionIndex < MAX_INGREDIENTS_POSITION_COUNT; ++startPositionIndex)
			{
				Ingredient copiedKiln[MAX_KILN_SIZE][MAX_KILN_SIZE];
				CopyKiln(copiedKiln, kiln);

				int kilnRow = 0;
				int kilnCol = 0;

				int ingredientsRow = 0;
				int ingredientsCol = 0;

				for (int row = 0; row < MAX_INGREDIENTS_SIZE; ++row)
				{
					kilnRow = INGREDIENTS_START_POSITION[startPositionIndex].Row + row;
					for (int col = 0; col < MAX_INGREDIENTS_SIZE; ++col)
					{
						kilnCol = INGREDIENTS_START_POSITION[startPositionIndex].Col + col;

						switch (rotation)
						{
						case eRotationCW::Degree0:
							ingredientsRow = row;
							ingredientsCol = col;

							break;

						case eRotationCW::Degree90:
							ingredientsRow = MAX_INGREDIENTS_SIZE - 1 - col;
							ingredientsCol = row;

							break;

						case eRotationCW::Degree180:
							ingredientsRow = MAX_INGREDIENTS_SIZE - 1 - row;
							ingredientsCol = MAX_INGREDIENTS_SIZE - 1 - col;

							break;

						case eRotationCW::Degree270:
							ingredientsRow = col;
							ingredientsCol = MAX_INGREDIENTS_SIZE - 1 - row;

							break;
						}

						copiedKiln[kilnRow][kilnCol].Quality += sIngredients[ingredientsIndex][ingredientsRow][ingredientsCol].Quality;
						if (copiedKiln[kilnRow][kilnCol].Quality < 0)
						{
							copiedKiln[kilnRow][kilnCol].Quality = 0;
						}
						else if (copiedKiln[kilnRow][kilnCol].Quality > 9)
						{
							copiedKiln[kilnRow][kilnCol].Quality = 9;
						}

						copiedKiln[kilnRow][kilnCol].Color =
							sIngredients[ingredientsIndex][ingredientsRow][ingredientsCol].Color == eColor::White ?
							copiedKiln[kilnRow][kilnCol].Color : sIngredients[ingredientsIndex][ingredientsRow][ingredientsCol].Color;
					}
				}

				GetBestQualityBombRecursive(ingredientsCount + 1, maxIngredientsCount, copiedKiln, visited);
			}
		}

		visited[ingredientsIndex] = false;
	}
}

int main()
{
	unsigned int maxIngredientsCount = 0;
	std::cin >> maxIngredientsCount;

	for (unsigned int i = 0; i < maxIngredientsCount; ++i)
	{
		for (int row = 0; row < MAX_INGREDIENTS_SIZE; ++row)
		{
			for (int col = 0; col < MAX_INGREDIENTS_SIZE; ++col)
			{
				std::cin >> sIngredients[i][row][col].Quality;
			}
		}

		for (int row = 0; row < MAX_INGREDIENTS_SIZE; ++row)
		{
			for (int col = 0; col < MAX_INGREDIENTS_SIZE; ++col)
			{
				char colorChar;
				std::cin >> colorChar;

				eColor color;
				switch (colorChar)
				{
				case 'W':
					color = eColor::White;
					break;
				case 'R':
					color = eColor::Red;
					break;
				case 'B':
					color = eColor::Blue;
					break;
				case 'G':
					color = eColor::Green;
					break;
				case 'Y':
					color = eColor::Yellow;
					break;
				default:
					assert(false);
					break;
				}

				sIngredients[i][row][col].Color = color;
			}
		}
	}

	Ingredient kiln[MAX_KILN_SIZE][MAX_KILN_SIZE] = { 0, };
	bool visited[MAX_INGREDIENTS_COUNT] = { false, };

	GetBestQualityBombRecursive(0, maxIngredientsCount, kiln, visited);

	std::cout << sBestQualityBomb;

	return 0;
}


