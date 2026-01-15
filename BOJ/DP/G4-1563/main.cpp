
#include <iostream>

#define MAX_DAYS_COUNT (1001U)
#define DIVISOR (1000000U)

#define MAX_ATTENDANCE_STATES (3U) // 0: O, 1: A, 2: AA
#define MAX_LATES_COUNT (2U)

static unsigned int sAttendanceAwardCases[MAX_DAYS_COUNT][MAX_ATTENDANCE_STATES][MAX_LATES_COUNT] = { 0, };

int main()
{
    unsigned int daysCount;
    std::cin >> daysCount;

    sAttendanceAwardCases[1][0][0] = 1;
    sAttendanceAwardCases[1][0][1] = 1;
    sAttendanceAwardCases[1][1][0] = 1;

    for (unsigned int day = 2; day <= daysCount; ++day)
    {
        unsigned int lastDay = day - 1;

        sAttendanceAwardCases[day][0][0] = (sAttendanceAwardCases[lastDay][0][0] + sAttendanceAwardCases[lastDay][1][0] + sAttendanceAwardCases[lastDay][2][0]) % DIVISOR;
        sAttendanceAwardCases[day][0][1] = (sAttendanceAwardCases[lastDay][0][1] + sAttendanceAwardCases[lastDay][1][1] + sAttendanceAwardCases[lastDay][2][1] +
                                           sAttendanceAwardCases[day][0][0]) % DIVISOR;

        sAttendanceAwardCases[day][1][0] = sAttendanceAwardCases[lastDay][0][0];
        sAttendanceAwardCases[day][1][1] = sAttendanceAwardCases[lastDay][0][1];

        sAttendanceAwardCases[day][2][0] = sAttendanceAwardCases[lastDay][1][0];
        sAttendanceAwardCases[day][2][1] = sAttendanceAwardCases[lastDay][1][1];
    }

    unsigned int attendanceAwardCount = 0;
    for (unsigned int i = 0; i < MAX_ATTENDANCE_STATES; ++i)
    {
        for (unsigned int j = 0; j < MAX_LATES_COUNT; ++j)
        {
            attendanceAwardCount = (attendanceAwardCount + sAttendanceAwardCases[daysCount][i][j]) % DIVISOR;
        }
    }
    
    std::cout << attendanceAwardCount;

    return 0;
}