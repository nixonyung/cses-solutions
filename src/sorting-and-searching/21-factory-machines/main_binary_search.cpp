#include "utils.hpp"
#include <algorithm>

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto target = read<uint>();
    auto machine_durations = std::vector<uint>(n);
    {
        for (auto &input : machine_durations) {
            input = read<uint>();
        }
    }

    // (ref.) [CSES - Factory Machines](https://usaco.guide/problems/cses-1620-factory-machines/solution)

    auto ans = *std::ranges::lower_bound(
        iota(
            1UL,
            (ulong)*std::ranges::min_element(machine_durations) * target + 1
        ),
        true,
        {},
        [&machine_durations, target](auto const &time) {
            ulong num_products = 0;
            for (auto const &machine_duration : machine_durations) {
                num_products += time / machine_duration;
                if (num_products >= target) {
                    return true;
                }
            }
            return false;
        }
    );
    std::cout << ans << '\n';
}