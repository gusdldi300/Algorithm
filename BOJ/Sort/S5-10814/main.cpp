
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Customer
{
    unsigned int Age;
    //unsigned int RegisteredRank;
    std::string Name;
};

static bool CompareCustomer(const Customer& first, const Customer& second)
{
    /*
    if (first.Age == second.Age)
    {
        first.RegisteredRank < second.RegisteredRank;
    }
    */

    return first.Age < second.Age;
}

int main()
{
    unsigned int customersCount;
    std::cin >> customersCount;

    std::vector<Customer> customersOrdered;
    for (unsigned int i = 0; i < customersCount; ++i)
    {
        Customer customer;
        std::cin >> customer.Age >> customer.Name;
        //customer.RegisteredRank = i;

        customersOrdered.push_back(customer);
    }

    std::stable_sort(customersOrdered.begin(), customersOrdered.end(), CompareCustomer);

    for (const Customer& customer : customersOrdered)
    {
        std::cout << customer.Age << " " << customer.Name << std::endl;
    }

    return 0;
}
