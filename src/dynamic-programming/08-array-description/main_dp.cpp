#include <iostream>
#include <vector>

namespace {
const unsigned long MOD = 1e9 + 7;
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned NUM_UPPER_BOUND;
    {
        std::cin >> N >> NUM_UPPER_BOUND;
    }

    auto num_wayss = std::vector<unsigned long>(NUM_UPPER_BOUND + 2);
    {
        // dummy values to handle out-of-bound
        num_wayss[0] = 0;
        num_wayss[NUM_UPPER_BOUND + 1] = 0;

        auto new_num_wayss = num_wayss;
        unsigned number;
        for (unsigned number_idx = 0; number_idx < N; number_idx++) {
            std::cin >> number;
            for (unsigned i = 1; i <= NUM_UPPER_BOUND; i++) { // iterate possible ending values
                new_num_wayss[i] = (number != i && number != 0) ? 0
                                   : (number_idx != 0)          ? (num_wayss[i - 1] + num_wayss[i] + num_wayss[i + 1]) % MOD
                                                                : 1;
            }
            std::swap(num_wayss, new_num_wayss);
        }
    }
    {
        unsigned long num_wayss_sum = 0;
        for (auto const &num_ways : num_wayss) {
            num_wayss_sum += num_ways;
        }
        std::cout << num_wayss_sum % MOD << '\n';
    }
}