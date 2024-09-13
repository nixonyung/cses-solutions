#include "utils.hpp"
#include <set>

int main() {
    enable_fast_io();

    auto street_len = read<uint>();
    auto n = read<uint>();

    // (ref.) [CSES - Traffic Lights - Solution 2](https://usaco.guide/problems/cses-1163-traffic-lights/solution#solution-2---going-backwards)

    auto light_poss = std::vector<uint>(n);
    auto light_poss_set = std::set<uint>{0, street_len}; // dummy values to handle out-of-bound
    {
        for (auto i : iota(0U, n)) {
            auto light_pos = read<uint>();
            light_poss[i] = light_pos;
            light_poss_set.insert(light_pos);
        }
    }

    auto anss = std::vector<uint>(n);
    {
        // find anss[n-1]
        {
            anss[n - 1] = 0;
            uint prev_light_pos = *light_poss_set.begin();
            for (auto light_pos : light_poss_set | std::views::drop(1)) {
                anss[n - 1] = std::max(anss[n - 1], light_pos - prev_light_pos);
                prev_light_pos = light_pos;
            }
        }

        // find ans from the end
        // anss[i] can be obtained by removing light_poss[i+1] from anss[i+1]
        for (auto i : iota(0U, n - 1) | std::views::reverse) {
            auto it = light_poss_set.find(light_poss[i + 1]);
            anss[i] = std::max(anss[i + 1], *std::next(it) - *std::prev(it));
            light_poss_set.erase(it);
        }
    }
    for (auto const &ans : anss) {
        std ::cout << ans << ' ';
    }
    std::cout << '\n';
}