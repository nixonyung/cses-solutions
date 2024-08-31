#define VERSION_REAL_TIME 1
#define VERSION_OFFLINE 2

#define VERSION VERSION_OFFLINE

#if VERSION == VERSION_REAL_TIME
#include "../../lib/cses_io.hpp"
#include <iterator>
#include <set>

int main() {
    cses::enable_fast_io();

    auto [x, n] = cses::read_tuple<int, int>();

    // (ref.) [CSES - Traffic Lights - Solution 1](https://usaco.guide/problems/cses-1163-traffic-lights/solution#solution-1)
    auto poss = std::set<int>{0, x};
    auto lengths = std::multiset<int>{x};
    for (auto i = 0; i < n; i++) {
        auto p = cses::read<int>();

        auto it = poss.insert(p).first;
        auto next = std::next(it);
        auto prev = std::prev(it);
        lengths.erase(lengths.find(*next - *prev));
        lengths.insert(*next - *it);
        lengths.insert(*it - *prev);
        std::cout << *std::prev(lengths.end()) << ' ';
    }
    std::cout << '\n';
}
#elif VERSION == VERSION_OFFLINE
#include "../../lib/cses_io.hpp"
#include <iterator>
#include <set>

int main() {
    cses::enable_fast_io();

    auto [x, n] = cses::read_tuple<int, int>();

    // (ref.) [CSES - Traffic Lights - Solution 2](https://usaco.guide/problems/cses-1163-traffic-lights/solution#solution-2---going-backwards)
    auto poss = cses::read_vector<int>(n);
    auto poss_sorted = std::set(poss.begin(), poss.end());
    {
        // dummy values to handle out-of-bound
        poss_sorted.insert(0);
        poss_sorted.insert(x);
    }

    auto anss = std::vector<int>(n);
    {
        anss[n - 1] = 0;

        auto prev_pos = *poss_sorted.begin();
        for (auto it = std::next(poss_sorted.begin()); it != poss_sorted.end(); it++) {
            auto pos = *it;
            anss[n - 1] = std::max(anss[n - 1], pos - prev_pos);
            prev_pos = pos;
        }

        for (auto i = n - 1; i > 0; i--) {
            auto it = poss_sorted.find(poss[i]);
            anss[i - 1] = std::max(anss[i], *std::next(it) - *std::prev(it));
            poss_sorted.erase(it);
        }
    }
    cses::print_range(anss);
}
#endif