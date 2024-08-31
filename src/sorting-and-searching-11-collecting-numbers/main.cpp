#include "../../lib/cses_io.hpp"

int main() {
    cses::enable_fast_io();

    auto n = cses::read<int>();

    auto poss = std::vector<int>(n);
    for (auto i = 0; i < n; i++) {
        poss[cses::read<int>()] = i;
    }

    // ans is the number of increasing subsequence in `pos`
    auto ans = 1;
    for (auto i = 1; i <= n - 1; i++) {
        if (poss[i] > poss[i + 1]) {
            ans++;
        }
    }
    std::cout << ans << '\n';
}