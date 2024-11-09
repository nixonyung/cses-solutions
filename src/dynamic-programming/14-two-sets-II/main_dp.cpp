#include <iostream>
#include <vector>

namespace {
const unsigned long MOD = 1e9 + 7;
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }
    // see introductory-problems/08-two-sets
    if (!((N - 1) & 2)) {
        std::cout << 0 << '\n';
        return 0;
    }
    unsigned const numbers_sum = N * (N + 1) / 2;

    auto num_wayss = std::vector<unsigned long>(numbers_sum + 1, 0);
    {
        num_wayss[0] = 1;

        for (unsigned number = 1; number <= N; number++) {
            for (unsigned i = numbers_sum; i >= number; i--) {
                num_wayss[i] = (num_wayss[i] + num_wayss[i - number]) % (MOD * 2); // (x/2) % MOD = (x % (MOD*2)) / 2
            }
        }
    }
    std::cout << num_wayss[numbers_sum / 2] / 2 << '\n'; // eliminate double counting
}