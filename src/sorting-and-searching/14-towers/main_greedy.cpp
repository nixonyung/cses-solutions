// greedy solution: put new cube to the tower with the smallest top larger than the new cube

#include <iostream>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    auto tower_tops = std::multiset<unsigned>();
    {
        decltype(tower_tops)::value_type cube_size;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> cube_size;

            auto it = tower_tops.upper_bound(cube_size);
            if (it != tower_tops.end()) tower_tops.extract(it);
            tower_tops.insert(cube_size);
        }
    }
    std::cout << tower_tops.size() << '\n';
}