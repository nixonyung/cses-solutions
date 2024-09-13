#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto allowed_weight = read<uint>();
    auto weights = std::vector<uint>(n);
    {
        for (auto &weight : weights) {
            weight = read<uint>();
        }
    }

    // greedy solution: at each step, try to pick the smallest `p` and the largest `p`

    radix_sort(weights);

    // for (auto const &p : ps) {
    //     std::cout << p << ' ';
    // }
    // std::cout << '\n';

    uint ans = 0;
    {
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            if (weights[left] + weights[right] <= allowed_weight) {
                left++;
                right--;
            } else {
                right--;
            }
            ans++;
        }
    }
    std::cout << ans << '\n';
}