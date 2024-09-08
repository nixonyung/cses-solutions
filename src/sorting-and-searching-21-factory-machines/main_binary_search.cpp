#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto target = read<uint>();

    // (ref.) [CSES - Factory Machines](https://usaco.guide/problems/cses-1620-factory-machines/solution)

    auto machine_durations = std::vector<uint>(n);
    auto min_machine_duration = std::numeric_limits<uint>::max();
    {
        for (auto &input : machine_durations) {
            input = read<uint>();
            min_machine_duration = std::min(min_machine_duration, input);
        }
    }

    auto ans = find_first_valid(
        (ulong)min_machine_duration * target + 1,
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