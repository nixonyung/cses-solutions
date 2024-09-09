#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto num_subarrays = read<uint>();

    auto inputs = std::vector<uint>(n);
    ulong sum = 0;
    {
        for (auto &input : inputs) {
            input = read<uint>();
            sum += input;
        }
        if (num_subarrays == 1) {
            std::cout << sum << '\n';
            return 0;
        }
    }

    // (ref.) [CSES - Array Division](https://usaco.guide/problems/cses-1085-array-division/solution)

    auto ans = find_first_valid(
        sum,
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
            // define valid as `curr_num_subarrays <= num_subarrays` to fulfill `find_first_valid`'s assumption
            //
            // the first valid pos should automatically achieve `curr_num_subarrays == num_subarrays`
            // because `curr_num_subarrays < num_subarrays` will never be the optimal solution
            // because the max_sum can always be made smaller by dividing the subarray
            return true;
        }
    );
    std::cout << ans << '\n';
}