
#include <cassert>
#include <iostream>


bool CanTransformeToTargetString(const std::string* curString, const std::string& targetString)
{
	if (curString->size() > targetString.size())
	{
		return false;
	}

	if (curString->size() == targetString.size() && *curString == targetString)
	{
		return true;
	}

	std::string* stringAddA = new std::string(*curString + 'A');
	if (CanTransformeToTargetString(stringAddA, targetString))
	{
		return true;
	}

	delete stringAddA;

	char* nextCharArray = new char[curString->size() + 2];
	nextCharArray[0] = 'B';

	unsigned int nextStringIndex = 1;
	for (auto reverse_iter = curString->rbegin(); reverse_iter != curString->rend(); ++reverse_iter)
	{
		nextCharArray[nextStringIndex++] = *reverse_iter;
	}

	nextCharArray[nextStringIndex] = '\0';

	std::string* stringAddBReversed = new std::string(nextCharArray);
	delete[] nextCharArray;
	if (CanTransformeToTargetString(stringAddBReversed, targetString))
	{
		return true;
	}

	delete stringAddBReversed;

	return false;
}

int main()
{
	std::string sourceString;
	std::string targetString;

	std::cin >> sourceString >> targetString;

	assert(sourceString.size() < targetString.size());
	if (CanTransformeToTargetString(&sourceString, targetString))
	{
		std::cout << 1;
	}
	else
	{
		std::cout << 0;
	}

	return 0;
}
