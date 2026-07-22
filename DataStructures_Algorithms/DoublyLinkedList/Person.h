#pragma once

#include "Person.h"

class Person
{
public:
    Person(const char* name, unsigned int age);
    ~Person();

    Person(Person&& other);

    bool operator==(const Person& other) const;
    
    const char* GetName() const;
    const unsigned int GetAge() const;

private:
    unsigned int getStringLength(const char* string) const;

private:
    char* mName;
    unsigned int mAge;
};



