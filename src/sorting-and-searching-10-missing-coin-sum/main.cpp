#include "../../lib/cses_io.hpp"
#include <algorithm>

int main() {
    cses::enable_fast_io();

    auto n = cses::read<int>();
    auto xs = cses::read_vector<int>(n);

    /*
    observe this:
        given any set of coins with max_sum, and any x not in the set:
            if x <= max_sum:
                We have 1 <= max_sum-x <= max_sum,
                then the set can create [max_sum-x+1, max_sum],
                then the set and x together can create [max_sum, max_sum+x].

                => We can add x to the set and then max_sum += x.
            else if x == max_sum+1:
                x itself creates max_sum+1.

                The set can create [1, max_sum],
                then the set and x together can create [x+1, max_sum+x], i.e. [max_sum+2, max_sum+x].

                => We can add x to the set and then max_sum += x.
            else: (x > max_sum+1)
                There is no way to create max_sum+1.
    */

    // greedy solution: try to pick the smallest `x`

    std::ranges::sort(xs);

    auto max_sum = 0L;
    for (auto i = 0; i < n; i++) {
        if (xs[i] > max_sum + 1) {
            std::cout << max_sum + 1 << '\n';
            return 0;
        }
        max_sum += xs[i];
    }
    std::cout << max_sum + 1 << '\n';
}