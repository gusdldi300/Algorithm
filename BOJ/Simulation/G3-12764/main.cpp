
#include <cassert>
#include <queue>
#include <vector>
#include <iostream>

struct User
{
	unsigned int StartTime;
	unsigned int EndTime;
	unsigned int UsingComputer;
};

struct UserStartTimeAscendComparator
{
	bool operator()(const User& firstUser, const User& secondUser)
	{
		return firstUser.StartTime > secondUser.StartTime;
	}
};

struct UserEndTimeAscendComparator
{
	bool operator()(const User& firstUser, const User& secondUser)
	{
		return firstUser.EndTime > secondUser.EndTime;
	}
};

struct UserUsingComputerAscendComparator
{
	bool operator()(const User& firstUser, const User& secondUser)
	{
		return firstUser.UsingComputer > secondUser.UsingComputer;
	}
};

int main()
{
	const int MAX_USER_COUNT = 100000;
	 
	unsigned int userCount = 0;
	std::cin >> userCount;
	assert(userCount <= MAX_USER_COUNT);

	unsigned int computerUsedCounts[MAX_USER_COUNT] = { 0, };

	std::priority_queue<User, std::vector<User>, UserStartTimeAscendComparator> startTimeAscendQueue;
	std::priority_queue<User, std::vector<User>, UserEndTimeAscendComparator> endTimeAscendQueue;
	std::priority_queue<User, std::vector<User>, UserUsingComputerAscendComparator> usingComputerAscendQueue;

	unsigned int startTime = 0;
	unsigned int endTime = 0;

	for (unsigned int i = 0; i < userCount; ++i)
	{
		std::cin >> startTime >> endTime;
		assert(startTime < endTime);
		assert(endTime <= 1000000);

		User user;
		user.StartTime = startTime;
		user.EndTime = endTime;
		user.UsingComputer = MAX_USER_COUNT;

		startTimeAscendQueue.push(user);
	}

	unsigned int addedComputer = 0;

	while (startTimeAscendQueue.empty() == false)
	{
		User currentUser = startTimeAscendQueue.top();
		startTimeAscendQueue.pop();
		
		while (endTimeAscendQueue.empty() == false)
		{
			User compareUser = endTimeAscendQueue.top();
			if (currentUser.StartTime < compareUser.EndTime)
			{
				break;
			}

			endTimeAscendQueue.pop();

			usingComputerAscendQueue.push(compareUser);
		}

		unsigned int usingComputer;
		if (usingComputerAscendQueue.empty())
		{
			usingComputer = addedComputer;
			++addedComputer;
		}
		else
		{
			usingComputer = usingComputerAscendQueue.top().UsingComputer;
			usingComputerAscendQueue.pop();
		}

		currentUser.UsingComputer = usingComputer;
		endTimeAscendQueue.push(currentUser);

		computerUsedCounts[usingComputer]++;
	}

	std::cout << addedComputer << std::endl;
	for (unsigned int i = 0; i < addedComputer; ++i)
	{
		std::cout << computerUsedCounts[i] << ' ';
	}

	return 0;
}