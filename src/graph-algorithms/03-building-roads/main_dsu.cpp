#include "disjoint_set_union.hpp"
#include <iostream>
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
        std::cout << dsu.get_num_parents() - 1 // exclude city0
                         - 1                   // num_new_edges = num_parents - 1
                  << '\n';

        uint curr_max_city = 1;
        for (int i = 1; std::cmp_less_equal(i, num_cities); i++) {
            auto const &parent = dsu.parent(i);
            if (parent > curr_max_city) {
                std::cout << curr_max_city << ' ' << parent << '\n';
                curr_max_city = parent;
            }
        }
    }
}