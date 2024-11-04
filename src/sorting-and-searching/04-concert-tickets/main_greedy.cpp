/*
given that each customer need to get a ticket at "real-time",
we need a data structure to sort the values and support O(logn) deletion (good enough for n <= 2e5).
    => use multiset ("set" but allow duplicates)
*/

#include <iostream>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_TICKETS;
    unsigned NUM_CUSTOMERS;
    {
        std::cin >> NUM_TICKETS >> NUM_CUSTOMERS;
    }
    auto tickets = std::multiset<unsigned>();
    {
        decltype(tickets)::value_type ticket;
        for (unsigned i = 0; i < NUM_TICKETS; i++) {
            std::cin >> ticket;
            tickets.insert(ticket);
        }
    }

    unsigned target;
    for (unsigned i = 0; i < NUM_CUSTOMERS; i++) {
        std::cin >> target;

        if (tickets.empty()) {
            std::cout << "-1\n";
            continue;
        }

        // (ref.) [Find largest element smaller than current with STL](https://stackoverflow.com/a/55087805)
        auto it = tickets.upper_bound(target);
        if (it == tickets.begin()) {
            std::cout << "-1\n";
            continue;
        }
        it--;
        std::cout << *it << '\n';
        tickets.extract(it);
    }
}