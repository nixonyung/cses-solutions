#include "../../lib/cses_io.hpp"
#include <algorithm>
#include <cstdlib>

int main() {
    cses::enable_fast_io();

    auto n = cses::read<int>();
    auto ps = cses::read_vector<int>(n);

    /*
    solution: use median as the target length
        if n is odd:
            choose p[n/2]
        if n is even:
            choose either p[n/2] or p[n/2 + 1]
            (p[n/2] is chosen here)
    */

    std::ranges::sort(ps);
    auto median = ps[n >> 1];

    auto ans = 0L;
    for (auto i = 0; i < n; i++) {
        ans += std::abs(ps[i] - median);
    }
    std::cout << ans << '\n';
}