
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>

#include <unordered_map>

#define STRING_LENGTH (64)

void reverse_string(char* string, unsigned int length)
{
	assert(string != nullptr);
	assert(length < STRING_LENGTH);

	char* start_p = string;
	char* end_p = string + length - 1;

	for (unsigned int i = 0; i < length / 2; ++i)
	{
		char temp = *start_p;
		*start_p = *end_p;
		*end_p = temp;

		++start_p;
		--end_p;
	}
}

bool CanTransformToTargetStringRecursive(char* transformedString, unsigned stringLength, const std::string& targetString)
{
	if (stringLength > targetString.size())
	{
		return false;
	}

	if (stringLength == targetString.size() && strcmp(transformedString, targetString.c_str()) == 0)
	{
		return true;
	}

	transformedString[stringLength] = 'A';
	transformedString[stringLength + 1] = '\0';
	if (CanTransformToTargetStringRecursive(transformedString, stringLength + 1, targetString))
	{
		return true;
	}

	transformedString[stringLength] = 'B';
	transformedString[stringLength + 1] = '\0';
	reverse_string(transformedString, stringLength + 1);
	if (CanTransformToTargetStringRecursive(transformedString, stringLength + 1, targetString))
	{
		return true;
	}

	reverse_string(transformedString, stringLength + 1);

	return false;
}

int main()
{
	std::string sourceString;
	std::string targetString;

	std::cin >> sourceString >> targetString;

	assert(sourceString.size() < targetString.size());

	char transformedString[STRING_LENGTH] = { 0, };
	strcpy(transformedString, sourceString.c_str());

	std::unordered_map<std::string, int> map;
	
	if (CanTransformToTargetStringRecursive(transformedString, sourceString.size(), targetString))
	{
		std::cout << 1;
	}
	else
	{
		std::cout << 0;
	}

	return 0;
}
