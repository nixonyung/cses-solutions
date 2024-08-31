#include "../../lib/cses_io.hpp"
#include <algorithm>

int main() {
    cses::enable_fast_io();

    auto [n, x] = cses::read_tuple<int, int>();
    auto ps = cses::read_vector<int>(n);

    // greedy solution: at each step, try to pick the smallest `p` and the largest `p`
    std::ranges::sort(ps);

    auto ans = 0;
    {
        auto left = 0;
        auto right = n - 1;
        while (left <= right) {
            if (ps[left] + ps[right] <= x) {
                left++;
                right--;
            } else {
                right--;
            }
            ans++;
        }
    }
    std::cout << ans << '\n';
}