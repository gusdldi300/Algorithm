
#include "Person.h"

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
