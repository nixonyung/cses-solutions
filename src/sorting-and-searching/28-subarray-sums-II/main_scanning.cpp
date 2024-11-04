// (ref.) [CSES - Subarray Sums II](https://usaco.guide/problems/cses-1661-subarray-sums-ii/solution)

#include <iostream>
#include <map>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned TARGET;
    {
        std::cin >> N >> TARGET;
    }

    unsigned long num_subarrays = 0;
    {
        auto inputs = std::vector<int>(N);
        auto prefix_sum_counter = std::map<long, unsigned>{
            {0, 1}
        };
        decltype(prefix_sum_counter)::key_type prefix_sum = 0;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> inputs[i];

            prefix_sum += inputs[i];
            num_subarrays += prefix_sum_counter[prefix_sum - TARGET]; // want curr_sum - prefix_sum = target
            prefix_sum_counter[prefix_sum]++;
        }
    }
    std::cout << num_subarrays << '\n';
}