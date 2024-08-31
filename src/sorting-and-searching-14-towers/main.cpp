#include "../../lib/cses_io.hpp"
#include <set>

int main() {
    cses::enable_fast_io();

    auto n = cses::read<int>();

    // greedy solution: put k to the smallest tower larger than k
    auto tower_tops = std::multiset<int>();
    while (n--) {
        auto k = cses::read<int>();

        auto it = tower_tops.upper_bound(k);
        if (it != tower_tops.end()) {
            tower_tops.erase(it);
        }
        tower_tops.insert(k);
    }
    std::cout << tower_tops.size() << '\n';
}