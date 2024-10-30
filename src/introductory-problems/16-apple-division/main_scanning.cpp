#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }
    auto weights = std::vector<unsigned>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> weights[i];
        }
    }

    unsigned long min_weight_sums_diff;
    {
        decltype(min_weight_sums_diff) weights_sum1 = 0;
        decltype(min_weight_sums_diff) weights_sum2 = 0;
        {
            for (auto const &p : weights) {
                weights_sum1 += p;
            }
        }
        min_weight_sums_diff = weights_sum1;

        // if the k-th bit == 0, assign apple_k to group 1, else to group 2
        // optimization: using "iterative Gray code"
        unsigned bitmask = 0;
        for (unsigned i = 1; i < 1U << N; i++) {
            auto const k = std::countr_zero(i);

            bitmask ^= 1U << k;
            if (bitmask & (1U << k)) {
                weights_sum1 -= weights[k];
                weights_sum2 += weights[k];
            } else {
                weights_sum1 += weights[k];
                weights_sum2 -= weights[k];
            }
            min_weight_sums_diff = std::min(
                min_weight_sums_diff,
                (weights_sum1 > weights_sum2) ? (weights_sum1 - weights_sum2)
                                              : (weights_sum2 - weights_sum1)
            );
        }
    }
    std::cout << min_weight_sums_diff << '\n';
}
