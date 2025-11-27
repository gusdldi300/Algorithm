#include <iostream>

#define MAX_CARD_COUNT (1001U)

static unsigned int sMaxPayments[MAX_CARD_COUNT] = { 0, };

int main()
{
    int cardCount = 0;
    std::cin >> cardCount;

    for (int card = 1; card <= cardCount; ++card)
    {
        unsigned int maxPayment = 0;
        std::cin >> maxPayment;

        for (int maxPaymentIndex = card; maxPaymentIndex >= (card / 2); --maxPaymentIndex)
        {
            maxPayment = std::max(maxPayment, sMaxPayments[maxPaymentIndex] + sMaxPayments[card - maxPaymentIndex]);
        }

        sMaxPayments[card] = maxPayment;
    }

    std::cout << sMaxPayments[cardCount];

    return 0;
}