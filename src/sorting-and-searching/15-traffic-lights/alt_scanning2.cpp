// (ref.) [CSES - Traffic Lights - Solution 1](https://usaco.guide/problems/cses-1163-traffic-lights/solution#solution-1)

#include <iostream>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned STREET_LEN;
    unsigned NUM_LIGHTS;
    {
        std::cin >> STREET_LEN >> NUM_LIGHTS;
    }
    auto light_poss = std::set<unsigned>{0, STREET_LEN};
    decltype(light_poss)::value_type light_pos;
    auto lengths = std::multiset<unsigned>{STREET_LEN};
    for (unsigned i = 0; i < NUM_LIGHTS; i++) {
        std::cin >> light_pos;

        auto it = light_poss.insert(light_pos).first;
        auto next = std::next(it);
        auto prev = std::prev(it);
        lengths.extract(lengths.find(*next - *prev));
        lengths.insert(*next - *it);
        lengths.insert(*it - *prev);
        std::cout << *std::prev(lengths.end()) << ' ';
    }
    std::cout << '\n';
}
