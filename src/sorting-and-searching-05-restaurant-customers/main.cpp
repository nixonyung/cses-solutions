#include "../../lib/cses_io.hpp"
#include <algorithm>

int main() {
    cses::enable_fast_io();

    /*
    implementations that won't work:
        - store counters for all a,b
            => a,b <= 1e9 is too large
    */

    auto n = cses::read<int>();
    auto as = std::vector<int>(n);
    auto bs = std::vector<int>(n);
    for (auto i = 0; i < n; i++) {
        std::cin >> as[i] >> bs[i];
    }

    // direct implementation of the problem using pointers

    std::ranges::sort(as);
    std::ranges::sort(bs);

    auto ans = 0;
    {
        auto a_idx = 0;
        auto b_idx = 0;
        auto curr_num = 0;
        while (a_idx < n) {
            if (as[a_idx] < bs[b_idx]) {
                curr_num++;
                ans = std::max(ans, curr_num);
                a_idx++;
            } else if (as[a_idx] < bs[b_idx]) {
                curr_num--;
                b_idx++;
            } else {
                a_idx++;
                b_idx++;
            }
        }
        // there maybe bs not yet processed, but they can be skipped
        // because processing them will only decrement curr_num and thus will not change ans
    }
    std::cout << ans << '\n';
}