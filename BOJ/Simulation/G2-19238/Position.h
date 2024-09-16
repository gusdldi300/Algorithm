#pragma once

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