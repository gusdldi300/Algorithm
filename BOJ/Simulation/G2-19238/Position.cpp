
#include "Position.h"

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
