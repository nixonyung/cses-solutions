#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto inputs = std::vector<uint>(n);
    {
        for (auto &input : inputs) {
            input = read<uint>();
        }
    }

    /*
    observe that:
        given any set of coins with max_sum (i.e. the coins can create [1,max_sum]), and any x not in the set:
            if x <= max_sum+1:
                the set and x can create [1,max_sum+x]
            else: (x > max_sum+1)
                There is no way to create max_sum+1.

    greedy solution: try to pick the smallest `x` while `x <= max_sum+1`
    */

    radix_sort(inputs);

    auto max_creatable_sum = 0L;
    for (auto const &input : inputs) {
        if (input > max_creatable_sum + 1) {
            std::cout << max_creatable_sum + 1 << '\n';
            return 0;
        }
        max_creatable_sum += input;
    }
    std::cout << max_creatable_sum + 1 << '\n';
}