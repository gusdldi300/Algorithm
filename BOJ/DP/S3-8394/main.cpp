
#include <iostream>
#include <cassert>

#define MAX_PARTICIPANTS (10000001U)
#define HANDSHAKE_CASES (2U)

#define PRINT_DIGIT_DIVISOR (10U)

enum HandShake
{
    False = 0,
    True
};

unsigned int sHandShakes[HANDSHAKE_CASES][MAX_PARTICIPANTS] = { 0, };

int main()
{
    unsigned int targetParticipant = 0;

    std::cin >> targetParticipant;
    assert(targetParticipant >= 1 && targetParticipant < MAX_PARTICIPANTS);

    sHandShakes[HandShake::False][1] = 1;
    sHandShakes[HandShake::True][1] = 0;

    for (unsigned int participant = 2; participant <= targetParticipant; ++participant)
    {
        unsigned int lastParticipant = participant - 1;
        sHandShakes[HandShake::False][participant] = (sHandShakes[HandShake::False][lastParticipant] + sHandShakes[HandShake::True][lastParticipant]) % PRINT_DIGIT_DIVISOR;
        sHandShakes[HandShake::True][participant] = sHandShakes[HandShake::False][lastParticipant];
    }

    std::cout << ((sHandShakes[HandShake::False][targetParticipant] + sHandShakes[HandShake::True][targetParticipant]) % PRINT_DIGIT_DIVISOR);

    return 0;
}