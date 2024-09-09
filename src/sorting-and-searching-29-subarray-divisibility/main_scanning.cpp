#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    ulong num_subarrays = 0;
    {
        auto inputs = std::vector<int>(n);
        long curr_mod_sum = 0;
        auto prefix_mod_sum_counter = std::vector<uint>(n);
        {
            prefix_mod_sum_counter[0] = 1;
        }
        for (auto i : iota(0U, n)) {
            inputs[i] = read<int>();
            // (ref.) [Fastest way to get a positive modulo in C/C++](https://stackoverflow.com/questions/14997165/fastest-way-to-get-a-positive-modulo-in-c-c)
            curr_mod_sum = ((curr_mod_sum + inputs[i]) % n + n) % n;
            num_subarrays += prefix_mod_sum_counter[curr_mod_sum]; // want curr_mod_sum - prefix_mod_sum = 0
            prefix_mod_sum_counter[curr_mod_sum]++;
        }
    }
    std::cout << num_subarrays << '\n';
}