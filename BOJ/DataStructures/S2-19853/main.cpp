#include <string>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

#define HOUR_MIN_DIVIDE_INDEX (2U)

class Time
{
public:
    Time(const std::string& timeString)
    {
        assert(timeString[HOUR_MIN_DIVIDE_INDEX] == ':');

        std::string hourString = timeString.substr(0, HOUR_MIN_DIVIDE_INDEX);
        std::string minString = timeString.substr(HOUR_MIN_DIVIDE_INDEX + 1);

        mHour = std::stoi(hourString);
        mMinute = std::stoi(minString);
    }

    bool IsLessEqual(const Time& other) const
    {
        if (mHour > other.mHour)
        {
            return false;
        }
        else if (mHour < other.mHour)
        {
            return true;
        }
        
        if (mMinute > other.mMinute)
        {
            return false;
        }

        return true;
    }

    bool IsGreatEqual(const Time& other) const
    {
        if (mHour < other.mHour)
        {
            return false;
        }
        else if (mHour > other.mHour)
        {
            return true;
        }

        if (mMinute < other.mMinute)
        {
            return false;
        }

        return true;
    }

public:
    int mHour;
    int mMinute;
};

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    std::string startTimeString;
    std::string endTimeHourString;
    std::string streamEndTimeString;

    std::cin >> startTimeString >> endTimeHourString >> streamEndTimeString;
    
    Time startTime(startTimeString);
    Time endTime(endTimeHourString);
    Time streamEndTime(streamEndTimeString);

    std::unordered_set<std::string> entryNameSet;
    std::unordered_set<std::string> attendedNameSet;

    while (true)
    {
        std::string timeString;
        std::string name;

        std::cin >> timeString >> name;
        if (std::cin.fail())
        {
            break;
        }

        Time time(timeString);
        if (time.IsLessEqual(startTime))
        {
            // Enter
            entryNameSet.insert(name);

            continue;
        }

        // Exit
        if (time.IsGreatEqual(endTime) && time.IsLessEqual(streamEndTime))
        {
            if (entryNameSet.find(name) != entryNameSet.end())
            {
                attendedNameSet.insert(name);
            }
        }
    }

    std::cout << attendedNameSet.size();
    
    return 0;
}