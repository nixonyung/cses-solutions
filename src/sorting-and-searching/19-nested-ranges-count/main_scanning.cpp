// (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Nested%20Ranges%20Count.cpp>
// (ref.) <https://cses.fi/problemset/hack/2169/entry/7621796/>

#include "fenwick_tree.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    struct Range {
        unsigned id;
        unsigned x;
        unsigned y;
    };
    auto ranges = std::vector<Range>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> ranges[i].x >> ranges[i].y;
            ranges[i].id = i;
        }
    }

    auto range_id_to_y_order = std::vector<unsigned>(N);
    {
        std::ranges::stable_sort(
            ranges,
            {},
            [](Range const &range) { return range.y; }
        );
        unsigned order = 0;
        range_id_to_y_order[ranges[0].id] = order;
        for (unsigned i = 1; i < N; i++) {
            if (ranges[i].y != ranges[i - 1].y) order++;
            range_id_to_y_order[ranges[i].id] = order;
        }
    }
    std::ranges::stable_sort(
        ranges,
        [](Range const &lhs, Range const &rhs) {
            return (lhs.x != rhs.x) ? (lhs.x < rhs.x)
                                    : (lhs.y > rhs.y);
        }
    );

    // reuse memory for the two questions
    auto anss = std::vector<unsigned>(N);
    auto tree = FenwickTree<unsigned>(N);
    {
        // solving the first question:
        // count how many ranges [l', r'] a range [l, r] contains, i.e. satisfying l <= l' <= r' <= r
        {
            for (unsigned i = N - 1; i <= N - 1; i--) {
                auto const &id = ranges[i].id;
                auto const &y_order = range_id_to_y_order[id];
                anss[id] = tree.prefix_sum(y_order);
                tree.update_at(y_order, 1);
            }
        }
        for (auto const &ans : anss) {
            std::cout << ans << ' ';
        }
        std::cout << '\n';

        // solving the second question:
        // count how many ranges [l', r'] contains the range [l, r], i.e. satisfying l' <= l <= r <= r'
        tree.clear();
        {
            for (unsigned i = 0; i < N; i++) {
                auto const &id = ranges[i].id;
                auto const &y_order = range_id_to_y_order[id];
                anss[id] = (y_order != 0) ? i - tree.prefix_sum(y_order - 1) : i;
                tree.update_at(range_id_to_y_order[ranges[i].id], 1);
            }
        }
        for (auto const &ans : anss) {
            std::cout << ans << ' ';
        }
        std::cout << '\n';
    }
}
