#include "disjoint_set_union.hpp"
#include <iostream>
#include <iterator>
#include <set>
#include <utility>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint num_cities, num_old_edges;
    {
        std::cin >> num_cities >> num_old_edges;
    }

    auto dsu = DisjointSetUnion<uint>(num_cities + 1);
    {
        uint city1, city2;
        for (int i = 0; std::cmp_less(i, num_old_edges); i++) {
            std::cin >> city1 >> city2;
            dsu.connect(city1, city2);
        }
    }
    {
        auto roots = std::set<uint>();
        {
            for (uint i = 1; i <= num_cities; i++) {
                roots.insert(dsu.root_id(i));
            }
        }
        std::cout << roots.size() - 1 << '\n';
        {
            auto prev_it = roots.begin();
            for (auto it = std::next(roots.begin()); it != roots.end(); it++) {
                std::cout << *prev_it << ' ' << *it << '\n';
                prev_it = it;
            }
        }
    }
}