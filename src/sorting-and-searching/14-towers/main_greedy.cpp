#include "utils.hpp"
#include <set>

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // greedy solution: put k to the smallest tower larger than k
    auto tower_tops = std::multiset<uint>();
    for (auto _ : iota(0U, n)) {
        auto input = read<uint>();
        auto it = tower_tops.upper_bound(input);
        if (it != tower_tops.end()) {
            tower_tops.erase(it);
        }
        tower_tops.insert(input);
    }
    std::cout << tower_tops.size() << '\n';
}