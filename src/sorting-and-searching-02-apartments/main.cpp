#include "../../lib/cses_io.hpp"
#include <algorithm>
#include <iostream>

int main() {
    cses::enable_fast_io();

    auto [n, m, k] = cses::read_tuple<std::size_t, std::size_t, std::size_t>();
    auto as = cses::read_vector<int>(n);
    auto bs = cses::read_vector<int>(n);

    // greedy solution: at each step, try to pick the smallest `a` and the smallest `b`
    std::ranges::sort(as);
    std::ranges::sort(bs);

    auto ans = 0;
    {
        auto a_idx = 0;
        auto b_idx = 0;
        while (a_idx < n && b_idx < m) {
            if (as[a_idx] + k < bs[b_idx]) {
                a_idx++;
            } else if (bs[b_idx] + k < as[a_idx]) {
                b_idx++;
            } else {
                ans++;
                a_idx++;
                b_idx++;
            }
        }
    }
    std::cout << ans << '\n';
}