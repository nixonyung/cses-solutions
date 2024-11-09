/*
(ref.) [CSES DP section Editorial](https://codeforces.com/blog/entry/105092)

There are two types of towers:

  - type A (top is a 2-col block):
    _____
    |   |
    |...|

  - type B (top is two 1-col blocks):
    _____
    | | |
    |...|

Denote num_towerss[i*2 + 0] as the number of type A towers at height i (i = 0 represents the lowest floor),
       num_towerss[i*2 + 1] as the number of type B towers at height i.

Then the recurrence relationship is:

  - num_towerss[i*2 + 0] = 2 * num_towerss[(i-1)*2 + 0] + num_towerss[(i-1)*2 + 1]
    - we can get type A height `i` towers from type A height `i-1` towers by either:
      - extend the last 2-col block
      - start a new 2-col block
    - we can get type A height `i` towers from type B height `i-1` towers by either:
      - start a new 2-col block

  - num_towerss[i*2 + 1] = num_towerss[(i-1)*2 + 0] + 4 * num_towerss[(i-1)*2 + 1]
    - we can get type B height `i` towers from type A height `i-1` towers by either:
      - start two new 1-col blocks
    - we can get type B height `i` towers from type B height `i-1` towers by either:
      - extend the last 1-col blocks
      - extend the left 1-col block and start a new 1-col block at right
      - extend the right 1-col block and start a new 1-col block at left
      - start two new 1-col blocks
*/

#include <iostream>
#include <vector>

namespace {
const unsigned long MOD = 1e9 + 7;
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_TESTS;
    {
        std::cin >> NUM_TESTS;
    }

    auto num_towerss = std::vector<unsigned long>(4);
    {
        unsigned N = 1;
        num_towerss[2] = 1; // number of type A towers at N-1
        num_towerss[3] = 1; // number of type B towers at N=1

        decltype(N) new_N;
        while (NUM_TESTS--) {
            std::cin >> new_N;

            if (new_N > N) {
                num_towerss.resize(new_N * 2 + 2);
                for (unsigned i = N + 1; i <= new_N; i++) {
                    num_towerss[i * 2] = (num_towerss[i * 2 - 2] * 2 + num_towerss[i * 2 - 1]) % MOD;
                    num_towerss[i * 2 + 1] = (num_towerss[i * 2 - 2] + num_towerss[i * 2 - 1] * 4) % MOD;
                }
            }
            N = new_N;
            std::cout << (num_towerss[N * 2] + num_towerss[N * 2 + 1]) % MOD << '\n';
        }
    }
}