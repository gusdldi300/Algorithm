
#include "Person.h"

#include <cassert>
#include <string.h>

Person::Person(const char* name, unsigned int age)
    : mAge(age)
{
    unsigned int nameLength = getStringLength(name);
    mName = new char[nameLength + 1];

    memcpy(mName, name, nameLength + 1);
}

Person::~Person()
{
    delete[] mName;
}

Person::Person(Person&& other)
    : mName(other.mName)
    , mAge(other.mAge)
{
    other.mName = nullptr;
    other.mAge = 0;
}

bool Person::operator==(const Person& other) const
{
    if (other == *this)
    {
        return true;
    }

    if (mAge != other.mAge)
    {
        return false;
    }

    unsigned int nameLength = getStringLength(mName);
    unsigned int otherNameLength = getStringLength(other.mName);

    if (nameLength != otherNameLength)
    {
        return false;
    }

    for (unsigned int i = 0; i < nameLength; ++i)
    {
        if (mName[i] != other.mName[i])
        {
            return false;
        }
    }

    return true;
}

const char* Person::GetName() const
{
    return mName;
}

const unsigned int Person::GetAge() const
{
    return mAge;
}

unsigned int Person::getStringLength(const char* string) const
{
    assert(string != nullptr);

    const char* pChar = string;
    while (*pChar != '\0')
    {
        ++pChar;
    }

    assert(pChar - string > 0);

    return pChar - string;
}
