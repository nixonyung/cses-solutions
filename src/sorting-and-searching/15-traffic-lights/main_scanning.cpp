// (ref.) [CSES - Traffic Lights - Solution 2](https://usaco.guide/problems/cses-1163-traffic-lights/solution#solution-2---going-backwards)

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned STREET_LEN;
    unsigned NUM_LIGHTS;
    {
        std::cin >> STREET_LEN >> NUM_LIGHTS;
    }
    auto light_poss = std::vector<unsigned>(NUM_LIGHTS);
    auto light_poss_set = std::set<unsigned>{0, STREET_LEN}; // dummy values to handle out-of-bound
    {
        for (unsigned i = 0; i < NUM_LIGHTS; i++) {
            std::cin >> light_poss[i];
            light_poss_set.insert(light_poss[i]);
        }
    }

    auto max_length_at_k_lights = std::vector<unsigned>(NUM_LIGHTS);
    {
        max_length_at_k_lights[NUM_LIGHTS - 1] = STREET_LEN - *light_poss_set.rbegin();
        {
            decltype(light_poss)::value_type prev_light_pos = 0;
            for (auto const &light_pos : light_poss_set) {
                max_length_at_k_lights[NUM_LIGHTS - 1] = std::max(max_length_at_k_lights[NUM_LIGHTS - 1], light_pos - prev_light_pos);
                prev_light_pos = light_pos;
            }
        }

        for (unsigned k = NUM_LIGHTS - 2; k <= NUM_LIGHTS - 2; k--) {
            auto it = light_poss_set.find(light_poss[k + 1]);
            max_length_at_k_lights[k] = std::max(max_length_at_k_lights[k + 1], *std::next(it) - *std::prev(it));
            light_poss_set.extract(it);
        }
    }
    for (auto const &length : max_length_at_k_lights) {
        std ::cout << length << ' ';
    }
    std::cout << '\n';
}