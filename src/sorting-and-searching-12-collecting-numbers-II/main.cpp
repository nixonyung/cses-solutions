#include "../../lib/cses_io.hpp"
#include <algorithm>

inline auto delta(
    int               a,
    int               b,
    std::vector<int> &xs,
    std::vector<int> &pos
) {
    if (xs[a] + 1 == xs[b]) {
        return (pos[xs[a] - 1] > a)
               + (a > b)
               + (b > pos[xs[b] + 1]);
    } else if (xs[b] + 1 == xs[a]) {
        return (pos[xs[b] - 1] > b)
               + (b > a)
               + (a > pos[xs[a] + 1]);
    } else {
        return (pos[xs[a] - 1] > a) + (a > pos[xs[a] + 1])
               + (pos[xs[b] - 1] > b) + (b > pos[xs[b] + 1]);
    }
}

int main() {
    cses::enable_fast_io();

    auto [n, m] = cses::read_tuple<int, int>();

    auto pos = std::vector<int>(n + 2); // pos[x] is the position of x (so the first x has pos[x] = 1)
    {
        // dummy values to handle index-out-of-bound
        pos[0] = 0;
        pos[n + 1] = n + 1;
    }
    auto xs = std::vector<int>(n + 1); // xs[1] is the first x (pos=1)

    /*
    side properties:
        - xs[pos[x]] = x
        - pos[xs[i]] = i
    */

    for (auto i = 1; i <= n; i++) {
        xs[i] = cses::read<int>();
        pos[xs[i]] = i;
    }

    // ans is the number of increasing subsequence in `pos`
    auto ans = 1;
    for (auto i = 1; i <= n - 1; i++) {
        if (pos[i] > pos[i + 1]) {
            ans++;
        }
    }

    while (m--) {
        auto [a, b] = cses::read_tuple<int, int>();

        // for each swap, update ans only by the delta contributed by index a and b
        ans -= delta(a, b, xs, pos);
        std::swap(pos[xs[a]], pos[xs[b]]);
        std::swap(xs[a], xs[b]);
        ans += delta(a, b, xs, pos);

        std::cout << ans << '\n';
    }
}