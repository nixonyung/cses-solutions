#include "../../lib/cses_io.hpp"
#include <algorithm>
#include <unordered_map>

int main() {
    cses::enable_fast_io();

    auto n = cses::read<int>();

    auto ans = 0;
    {
        auto m = std::unordered_map<int, int>(n);
        auto left = 0;
        for (auto right = 0; right < n; right++) {
            auto k = cses::read<int>();

            // update left to the smallest index where there are no duplicates in [left, right]
            if (m.contains(k)) {
                left = std::max(left, m[k] + 1);
            }
            ans = std::max(ans, right - left + 1);
            m[k] = right;
        }
    }
    std::cout << ans << '\n';
}