#include "../../lib/cses_io.hpp"
#include <iostream>
#include <set>

int main() {
    cses::enable_fast_io();

    /*
    given that each customer need to get a ticket at "real-time",
    we need a data structure to sort the values and support O(logn) deletion (good enough for n <= 2e5).
        => use multiset ("set" but allow duplicates)
    */

    auto [n, m] = cses::read_tuple<int, int>();
    auto hs = cses::read_multiset<int>(n);

    while (m--) {
        auto t = cses::read<int>();

        if (hs.empty()) {
            std::cout << "-1\n";
            continue;
        }
        // (ref.) [Find largest element smaller than current with STL](https://stackoverflow.com/a/55087805)
        auto it = hs.upper_bound(t);
        if (it != hs.begin()) {
            it--;
            std::cout << *it << '\n';
            hs.erase(it);
        } else {
            std::cout << "-1\n";
        }
    }
}