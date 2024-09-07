#include "utils.hpp"
#include <set>

int main() {
    enable_fast_io();

    auto street_len = read<uint>();
    auto n = read<uint>();

    // (ref.) [CSES - Traffic Lights - Solution 1](https://usaco.guide/problems/cses-1163-traffic-lights/solution#solution-1)
    auto light_poss = std::set<uint>{0, street_len};
    auto lengths = std::multiset<uint>{street_len};
    for (auto _ : iota(0U, n)) {
        auto it = light_poss.insert(read<uint>()).first;
        auto next = std::next(it);
        auto prev = std::prev(it);
        lengths.erase(lengths.find(*next - *prev));
        lengths.insert(*next - *it);
        lengths.insert(*it - *prev);
        std::cout << *std::prev(lengths.end()) << ' ';
    }
    std::cout << '\n';
}
