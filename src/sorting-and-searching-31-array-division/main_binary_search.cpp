#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto num_subarrays = read<uint>();
    auto inputs = std::vector<uint>(n);
    {
        for (auto &input : inputs) {
            input = read<uint>();
        }
    }

    // (ref.) [CSES - Array Division](https://usaco.guide/problems/cses-1085-array-division/solution)

    ulong sum = 0;
    {
        for (auto const &input : inputs) {
            sum += input;
        }
    }
    if (num_subarrays == 1) {
        std::cout << sum << '\n';
        std::exit(0);
    }

    auto ans = *std::ranges::lower_bound(
        iota(0UL, sum),
        true,
        {},
        [&inputs, num_subarrays](auto const &target_max_sum) {
            ulong curr_sum = 0;
            uint curr_num_subarrays = 1;
            for (auto const &input : inputs) {
                if (input > target_max_sum) {
                    return false;
                }
                curr_sum += input;
                if (curr_sum > target_max_sum) {
                    curr_sum = input;
                    if (++curr_num_subarrays > num_subarrays) {
                        return false;
                    }
                }
            }
            // search for `curr_num_subarrays <= num_subarrays`
            //
            // the first valid pos should automatically achieve `curr_num_subarrays == num_subarrays`
            // because `curr_num_subarrays < num_subarrays` will never be the optimal solution
            // because the max_sum can always be made smaller by dividing the subarray
            return true;
        }
    );
    std::cout << ans << '\n';
}