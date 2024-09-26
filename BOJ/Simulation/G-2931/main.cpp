#include <iostream>
#include <cassert>

#define MAX_MAP_SIZE (25)
#define MAX_MOVE_DIRECTIONS (4)

enum class Pipe
{
	None,
	UpDown,
	LeftRight,
	Plus,
	RightDown,
	UpRight,
	LeftUp,
	LeftDown
};

typedef struct
{
	Pipe CurPipe;
	bool Gates[MAX_MOVE_DIRECTIONS];
} Block;

typedef struct
{
	int Row;
	int Col;
} Position;

typedef struct
{
	Position CurPosition;
	unsigned int Direction;
} Vector;

int sRowSize;
int sColSize;
Block sMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

Position sMoveDirections[MAX_MOVE_DIRECTIONS] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static bool IsInBoundary(int nextRow, int nextCol)
{
	if (nextRow < 0 || nextRow >= MAX_MAP_SIZE || nextCol < 0 || nextCol >= MAX_MAP_SIZE)
	{
		return false;
	}

	return true;
}

static Pipe GetPipe(int row, int col)
{
	uint8_t gateOpenFlags = 0;
	for (unsigned int i = 0; i < MAX_MOVE_DIRECTIONS; ++i)
	{
		int nextRow = row + sMoveDirections[i].Row;
		int nextCol = col + sMoveDirections[i].Col;

		if (IsInBoundary(nextRow, nextCol) == false)
		{
			continue;
		}

		unsigned int openGateIndex = (i + 2) % MAX_MOVE_DIRECTIONS;
		if (sMap[nextRow][nextCol].Gates[openGateIndex])
		{
			gateOpenFlags |= (1 << i);
		}
	}

	Pipe emptyPipe;
	switch (gateOpenFlags)
	{
	case 0b1111:
		emptyPipe = Pipe::Plus;
		break;
	case 0b0011:
		emptyPipe = Pipe::UpRight;
		break;
	case 0b0101:
		emptyPipe = Pipe::UpDown;
		break;
	case 0b0110:
		emptyPipe = Pipe::RightDown;
		break;
	case 0b1001:
		emptyPipe = Pipe::LeftUp;
		break;
	case 0b1010:
		emptyPipe = Pipe::LeftRight;
		break;
	case 0b1100:
		emptyPipe = Pipe::LeftDown;
		break;
	default:
		emptyPipe = Pipe::None;
		break;
	}

	return emptyPipe;
}

static bool GetDirection(int row, int col, unsigned int* outDirection)
{
	for (unsigned int i = 0; i < MAX_MOVE_DIRECTIONS; ++i)
	{
		int nextRow = row + sMoveDirections[i].Row;
		int nextCol = col + sMoveDirections[i].Col;

		if (IsInBoundary(nextRow, nextCol) == false)
		{
			continue;
		}

		int openGateIndex = (i + 2) % MAX_MOVE_DIRECTIONS;
		if (sMap[nextRow][nextCol].Gates[openGateIndex])
		{
			*outDirection = i;

			return true;
		}
	}

	return false;
}

static Pipe FindPipeInAllDirections(int row, int col, Vector* outVector)
{
	Pipe emptyPipe = Pipe::None;

	for (unsigned int i = 0; i < MAX_MOVE_DIRECTIONS; ++i)
	{
		sMap[row][col].Gates[i] = true;
	}

	for (unsigned int i = 0; i < MAX_MOVE_DIRECTIONS; ++i)
	{
		int nextRow = row + sMoveDirections[i].Row;
		int nextCol = col + sMoveDirections[i].Col;

		if (IsInBoundary(nextRow, nextCol) == false)
		{
			continue;
		}

		emptyPipe = GetPipe(nextRow, nextCol);
		if (emptyPipe != Pipe::None)
		{
			outVector->CurPosition.Row = nextRow;
			outVector->CurPosition.Col = nextCol;

			break;
		}
	}

	return emptyPipe;
}

int main()
{
	for (unsigned int row = 0; row < sRowSize; ++row)
	{
		for (unsigned int col = 0; col < sColSize; ++col)
		{
			for (unsigned int i = 0; i < MAX_MOVE_DIRECTIONS; ++i)
			{
				sMap[row][col].Gates[i] = false;
			}

			sMap[row][col].CurPipe = Pipe::None;
		}
	}

	std::cin >> sRowSize >> sColSize;
	Vector startVector = { { -1, -1 }, MAX_MOVE_DIRECTIONS };
	Vector endVector = { { -1, -1 }, MAX_MOVE_DIRECTIONS };
	Vector curVector = { { -1, -1 }, MAX_MOVE_DIRECTIONS };

	Pipe emptyPipe = Pipe::None;
	bool bFoundEmptyPipe = false;

	unsigned int curDirection = MAX_MOVE_DIRECTIONS;

	// Set Gates
	for (unsigned int row = 0; row < sRowSize; ++row)
	{
		std::string mapRowString;
		std::cin >> mapRowString;

		for (unsigned int col = 0; col < sColSize; ++col)
		{
			switch (mapRowString[col])
			{
			case 'M':
				startVector.CurPosition.Row = row;
				startVector.CurPosition.Col = col;
				break;
			case 'Z':
				endVector.CurPosition.Row = row;
				endVector.CurPosition.Col = col;
				break;
			case '|':
				sMap[row][col].CurPipe = Pipe::UpDown;

				sMap[row][col].Gates[0] = true;
				sMap[row][col].Gates[2] = true;
				break;
			case '-':
				sMap[row][col].CurPipe = Pipe::LeftRight;

				sMap[row][col].Gates[3] = true;
				sMap[row][col].Gates[1] = true;
				break;
			case '+':
				sMap[row][col].CurPipe = Pipe::Plus;

				sMap[row][col].Gates[0] = true;
				sMap[row][col].Gates[1] = true;
				sMap[row][col].Gates[2] = true;
				sMap[row][col].Gates[3] = true;
				break;
			case '1':
				sMap[row][col].CurPipe = Pipe::RightDown;

				sMap[row][col].Gates[1] = true;
				sMap[row][col].Gates[2] = true;
				break;
			case '2':
				sMap[row][col].CurPipe = Pipe::UpRight;

				sMap[row][col].Gates[0] = true;
				sMap[row][col].Gates[1] = true;
				break;
			case '3':
				sMap[row][col].CurPipe = Pipe::LeftUp;

				sMap[row][col].Gates[3] = true;
				sMap[row][col].Gates[0] = true;
				break;
			case '4':
				sMap[row][col].CurPipe = Pipe::LeftDown;

				sMap[row][col].Gates[3] = true;
				sMap[row][col].Gates[2] = true;
				break;
			default:
				break;
			}
		}
	}

	int row = startVector.CurPosition.Row;
	int col = startVector.CurPosition.Col;
	curDirection = MAX_MOVE_DIRECTIONS;

	if (GetDirection(row, col, &curDirection))
	{
		sMap[row][col].Gates[curDirection] = true;
		
		curVector.CurPosition.Row = row + sMoveDirections[curDirection].Row;
		curVector.CurPosition.Col = col + sMoveDirections[curDirection].Col;
		curVector.Direction = curDirection;
	}
	else
	{
		emptyPipe = FindPipeInAllDirections(row, col, &curVector);
		
		goto empty_pipe_found;
	}

	row = endVector.CurPosition.Row;
	col = endVector.CurPosition.Col;
	curDirection = MAX_MOVE_DIRECTIONS;
	if (GetDirection(row, col, &curDirection))
	{
		sMap[row][col].Gates[curDirection] = true;
	}
	else
	{
		emptyPipe = FindPipeInAllDirections(row, col, &curVector);

		goto empty_pipe_found;
	}

	assert(startVector.CurPosition.Row != -1 && startVector.CurPosition.Col != -1);
	assert(endVector.CurPosition.Row != -1 && endVector.CurPosition.Col != -1);

	while (true)
	{
		int row = curVector.CurPosition.Row;
		int col = curVector.CurPosition.Col;
		int lastDirection = curVector.Direction;

		Pipe curPipe = sMap[row][col].CurPipe;
		int nextDirection;

		switch (curPipe)
		{
		case Pipe::UpDown:
			// intentional fallthrough
		case Pipe::LeftRight:
			// intentional fallthrough
		case Pipe::Plus:
			nextDirection = lastDirection;
			
			break;
		case Pipe::UpRight:
			if (lastDirection == 2)
			{
				nextDirection = 1;
			}
			else
			{
				nextDirection = 0;
			}

			break;
		case Pipe::RightDown:
			if (lastDirection == 3)
			{
				nextDirection = 2;
			}
			else
			{
				nextDirection = 1;
			}

			break;
		case Pipe::LeftDown:
			if (lastDirection == 1)
			{
				nextDirection = 2;
			}
			else
			{
				nextDirection = 3;
			}

			break;
		case Pipe::LeftUp:
			if (lastDirection == 1)
			{
				nextDirection = 0;
			}
			else
			{
				nextDirection = 3;
			}

			break;
		default:
			/*
			if (row == endVector.Position.Row && col == endVector.Position.Col)
			{
				return;
			}
			*/

			bFoundEmptyPipe = true;
			break;
		}

		if (bFoundEmptyPipe)
		{
			break;
		}

		curVector.CurPosition.Row = row + sMoveDirections[nextDirection].Row;
		curVector.CurPosition.Col = col + sMoveDirections[nextDirection].Col;

		curVector.Direction = nextDirection;
	}

	emptyPipe = GetPipe(curVector.CurPosition.Row, curVector.CurPosition.Col);

empty_pipe_found:

	std::string emptyPipeString;
	switch (emptyPipe)
	{
	case Pipe::UpDown:
		emptyPipeString = '|';
		break;
	case Pipe::LeftRight:
		emptyPipeString = '-';
		break;
	case Pipe::Plus:
		emptyPipeString = '+';
		break;
	case Pipe::UpRight:
		emptyPipeString = '2';
		break;
	case Pipe::RightDown:
		emptyPipeString = '1';
		break;
	case Pipe::LeftDown:
		emptyPipeString = '4';
		break;
	case Pipe::LeftUp:
		emptyPipeString = '3';
		break;
	default:
		assert(false);
		break;
	}

	std::cout << (curVector.CurPosition.Row + 1) << " " << (curVector.CurPosition.Col + 1) << " " << emptyPipeString << std::endl;

	return 0;
}
