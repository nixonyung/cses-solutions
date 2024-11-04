// (ref.) [CSES - Sliding Median - Solution 3](https://usaco.guide/problems/cses-1076-sliding-median/solution#solution-3-order-statistic-tree)

#include "ordered_set.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned K;
    {
        std::cin >> N >> K;
    }

    struct Number {
        unsigned id;
        unsigned val;
    };
    auto number_vals = std::vector<decltype(Number::val)>(N);
    auto numbers_ordered = OrderedSet< // emulating an ordered_multiset
        Number,
        decltype([](Number const &lhs, Number const &rhs) {
            return (lhs.val != rhs.val) ? (lhs.val < rhs.val)
                                        : (lhs.id < rhs.id);
        })>();
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> number_vals[i];
            if (i >= K) numbers_ordered.erase(numbers_ordered.lower_bound({0, number_vals[i - K]}));
            numbers_ordered.insert({i, number_vals[i]});
            if (i >= K - 1) std::cout << numbers_ordered.find_by_order((K - 1) >> 1)->val << ' ';
        }
    }
    std::cout << '\n';
}