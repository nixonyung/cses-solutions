#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }
    auto scores = std::vector<int>(N);
    auto score_prefix_sums = std::vector<long>(N + 1);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> scores[i];
            score_prefix_sums[i] = ((i != 0) ? score_prefix_sums[i - 1] : 0) + scores[i];
        }
    }

    auto max_scores = std::vector<long>(N); // optimization: only storing max_scores for one iteration of interval_size
    {
        for (unsigned len = 1; len <= N; len++) {
            for (unsigned l = 0; l <= N - len; l++) {
                if (len == 1) {
                    max_scores[l] = scores[l];
                    continue;
                }
                unsigned const r = l + len - 1;
                auto const interval_sum = score_prefix_sums[r] - ((l != 0) ? score_prefix_sums[l - 1] : 0);
                max_scores[l] = std::max(
                    interval_sum - max_scores[l + 1], // take numbers[l], then opponent will get prev_max_scores[l+1]
                    interval_sum - max_scores[l]      // take numbers[r], then opponent will get prev_max_scores[l]
                );
            }
        }
    }
    std::cout << max_scores[0] << '\n';
}