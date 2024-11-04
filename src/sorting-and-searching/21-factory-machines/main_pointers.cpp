// (ref.) [CSES - Factory Machines](https://usaco.guide/problems/cses-1620-factory-machines/solution)

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned TARGET;
    {
        std::cin >> N >> TARGET;
    }
    auto machine_durations = std::vector<unsigned>(N);
    decltype(machine_durations)::value_type min_machine_duration = -1U;
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> machine_durations[i];
            min_machine_duration = std::min(min_machine_duration, machine_durations[i]);
        }
    }
    std::cout << *std::ranges::lower_bound(
                     std::views::iota(
                         1UL,
                         (unsigned long)min_machine_duration * TARGET + 1
                     ),
                     true,
                     {},
                     [TARGET, &machine_durations](auto const &t) {
                         unsigned long num_products = 0;
                         for (auto const &machine_duration : machine_durations) {
                             num_products += t / machine_duration;
                             if (num_products >= TARGET) return true;
                         }
                         return false;
                     }
                 )
              << '\n';
}