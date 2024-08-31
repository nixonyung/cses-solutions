#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = int();
    std::cin >> n;

    auto ps = std::vector<int>(n);
    for (auto &p : ps) {
        std::cin >> p;
    }

    /*
    solve by enumerating all possible bitmasks:
        for the k-th bit in the bitmask, if the bit == 0, assign pk to group 1, else to group 2
    */

    auto sum1 = long();
    auto sum2 = 0L;
    for (auto const &p : ps) {
        sum1 += p;
    }

    auto ans = sum1;
    auto bitmask = 0;
    // using "iterative Gray code" as an optimization
    for (auto i = 1; i < (1 << n); i++) {
        auto p_idx = __builtin_ctz(i);
        bitmask ^= 1 << p_idx;
        if (bitmask & (1 << p_idx)) {
            sum2 += ps[p_idx];
            sum1 -= ps[p_idx];
        } else {
            sum1 += ps[p_idx];
            sum2 -= ps[p_idx];
        }
        ans = std::min(ans, std::abs(sum1 - sum2));
    }
    std::cout << ans << '\n';
}
