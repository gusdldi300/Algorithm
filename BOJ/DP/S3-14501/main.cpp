
#include <iostream>

#define MAX_DAYS (16U)

struct Appointment
{
    unsigned int DaysTaken;
    unsigned int Profit;
};

static Appointment sAppointments[MAX_DAYS];
static unsigned int sProfits[MAX_DAYS] = { 0, };

int main()
{
    unsigned int targetDay = 0;
    std::cin >> targetDay;

    for (unsigned int day = 1; day <= targetDay; ++day)
    {
        std::cin >> sAppointments[day].DaysTaken >> sAppointments[day].Profit;
    }

    for (unsigned int day = 1; day <= targetDay; ++day)
    {
        unsigned int endDay = day + sAppointments[day].DaysTaken - 1;
        if (endDay <= targetDay)
        {
            sProfits[endDay] = std::max(sProfits[endDay], (sAppointments[day].Profit + sProfits[day - 1]));
        }

        sProfits[day] = std::max(sProfits[day], sProfits[day - 1]);
    }

    std::cout << sProfits[targetDay];

    return 0;
}
