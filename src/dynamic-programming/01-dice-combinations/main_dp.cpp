#include <iostream>
#include <vector>

namespace {
const unsigned NUM_DICE_FACES = 6;
const unsigned long MOD = 1e9 + 7;
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    auto num_wayss = std::vector<unsigned long>(NUM_DICE_FACES); // optimization: num_ways to get sum=k is `num_wayss[k % NUM_DICE_FACES]`
    {
        unsigned long num_wayss_sum = 0;
        for (unsigned i = 0; i < N; i++) {
            num_wayss_sum = (num_wayss_sum + MOD
                             - num_wayss[i % NUM_DICE_FACES]
                             + (num_wayss[i % NUM_DICE_FACES] = (i == 0)
                                                                    // the only way is to throw a "1"
                                                                    ? 1
                                                                    : (i < NUM_DICE_FACES)
                                                                          // throw a `i` directly or need to rethrow once
                                                                          ? 1 + num_wayss_sum
                                                                          // need more than one rethrows
                                                                          : num_wayss_sum
                             ))
                            % MOD;
        }
    }
    std::cout << num_wayss[(N - 1) % NUM_DICE_FACES] << '\n';
}