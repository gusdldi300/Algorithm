#pragma once

#include "Position.h"

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