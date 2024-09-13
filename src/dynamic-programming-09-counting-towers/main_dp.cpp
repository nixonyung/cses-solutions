#include "utils.hpp"

int main() {
    const ulong MOD = 1e9 + 7;

    enable_fast_io();

    auto num_tests = read<uint>();
    auto dp = std::vector<ulong>(1000000 * 2);
    while (num_tests--) {
        auto n = read<uint>();
        {
            /*
            (ref.) [CSES DP section Editorial](https://codeforces.com/blog/entry/105092)

            Classifying towers into these two types:

            - type A (top is a 2-col block):
              _____
              |   |
              |...|

            - type B (top is two 1-col blocks):
              _____
              | | |
              |...|

            Denote dp[i][0] as the number of type A towers at height i (i = 0 means the lowest floor),
                   dp[i][1] as the number of type B towers at height i.

            The recurrence relationship is:

                - dp[i][0] = 2 * dp[i-1][0] + dp[i-1][1]

                  - from type A towers, we can:
                    - extend the last 2-col block
                    - start a new 2-col block
                  - from type B towers, we can:
                    - start a new 2-col block

                - dp[i][1] = dp[i-1][0] + 4 * dp[i-1][1]

                  - from type A towers, we can:
                    - start two new 1-col blocks
                  - from type B towers, we can:
                    - extend the last 1-col blocks
                    - extend the left 1-col block and start a new 1-col block at right
                    - extend the right 1-col block and start a new 1-col block at left
                    - start two new 1-col blocks
            */

            // initial state
            dp[0] = 1;
            dp[1] = 1;

            // recurrence
            for (auto i : iota(0U, n - 1)) {
                dp[i * 2 + 2] = (dp[i * 2] * 2 +
                                 dp[i * 2 + 1]
                                ) %
                                MOD;
                dp[i * 2 + 3] = (dp[i * 2] +
                                 dp[i * 2 + 1] * 4) %
                                MOD;
            }
        }
        std::cout << (dp[n * 2 - 2] + dp[n * 2 - 1]) % MOD << '\n';
    }
}