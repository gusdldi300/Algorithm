
#include <iostream>
#include <vector>
#include <unordered_set>

#define MAX_SEATS_COUNT (41U)

#define NOT_CHANGED_SEAT_INDEX (0U)
#define CHANGED_SEAT_INDEX (1U)

static long long sSeatCases[MAX_SEATS_COUNT][CHANGED_SEAT_INDEX + 1] = { 0, };

int main()
{
    unsigned int seatsCount = 0;
    std::cin >> seatsCount;

    unsigned int fixedSeatsCount = 0;
    std::cin >> fixedSeatsCount;

    std::unordered_set<unsigned int> fixedSeats;
    for (unsigned int i = 0; i < fixedSeatsCount; ++i)
    {
        unsigned int fixedSeat;
        std::cin >> fixedSeat;

        fixedSeats.insert(fixedSeat);
    }

    bool bLastSeatFixed = (fixedSeats.find(1) != fixedSeats.end()) ? true : false;
    sSeatCases[1][0] = 1;

    for (unsigned int i = 2; i <= seatsCount; ++i)
    {
        unsigned int lastIndex = i - 1;
        sSeatCases[i][NOT_CHANGED_SEAT_INDEX] = sSeatCases[lastIndex][NOT_CHANGED_SEAT_INDEX] + sSeatCases[lastIndex][CHANGED_SEAT_INDEX];
        
        if (fixedSeats.find(i) != fixedSeats.end())
        {
            bLastSeatFixed = true;

            continue;
        }
        
        if (bLastSeatFixed)
        {
            bLastSeatFixed = false;

            continue;
        }

        sSeatCases[i][CHANGED_SEAT_INDEX] = sSeatCases[lastIndex][NOT_CHANGED_SEAT_INDEX];
    }

    std::cout << sSeatCases[seatsCount][NOT_CHANGED_SEAT_INDEX] + sSeatCases[seatsCount][CHANGED_SEAT_INDEX];

    return 0;
}