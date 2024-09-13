#include "utils.hpp"
#include <set>

int main() {
    enable_fast_io();

    /*
    given that each customer need to get a ticket at "real-time",
    we need a data structure to sort the values and support O(logn) deletion (good enough for n <= 2e5).
        => use multiset ("set" but allow duplicates)
    */

    auto num_tickets = read<uint>();
    auto num_customers = read<uint>();

    auto tickets = std::multiset<uint>();
    {
        for (auto _ : iota(0U, num_tickets)) {
            tickets.insert(read<uint>());
        }
    }

    while (num_customers--) {
        auto target = read<uint>();

        if (tickets.empty()) {
            std::cout << "-1\n";
            continue;
        }
        // (ref.) [Find largest element smaller than current with STL](https://stackoverflow.com/a/55087805)
        {
            auto it = tickets.upper_bound(target);
            if (it != tickets.begin()) {
                it--;
                std::cout << *it << '\n';
                tickets.erase(it);
            } else {
                std::cout << "-1\n";
            }
        }
    }
}