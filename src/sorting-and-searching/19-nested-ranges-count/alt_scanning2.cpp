#include "ordered_set.hpp"
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
        std::ranges::stable_sort(
            ranges,
            [](Range const &lhs, Range const &rhs) {
                return (lhs.x != rhs.x) ? (lhs.x < rhs.x)
                                        : (lhs.y > rhs.y);
            }
        );
    }

    // reuse memory for the two questions
    auto anss = std::vector<unsigned>(N);
    // emulating an ordered_multiset: use extra fields to ensure uniqueness of each `y`
    struct Y {
        unsigned id;
        unsigned val;
    };
    auto ys_ordered = OrderedSet<
        Y,
        decltype([](Y const &lhs, Y const &rhs) {
            return (lhs.val != rhs.val) ? (lhs.val < rhs.val)
                                        : (lhs.id < rhs.id);
        })>();
    {
        // solving the first question:
        // count how many ranges [l', r'] a range [l, r] contains, i.e. satisfying l <= l' <= r' <= r
        {
            for (unsigned i = N - 1; i < N; i--) {
                anss[ranges[i].id] = (unsigned)ys_ordered.order_of_key({N, ranges[i].y});
                ys_ordered.insert({ranges[i].id, ranges[i].y});
            }
        }
        for (auto const &ans : anss) {
            std::cout << ans << ' ';
        }
        std::cout << '\n';

        // solving the second question:
        // count how many ranges [l', r'] contains the range [l, r], i.e. satisfying l' <= l <= r <= r'
        ys_ordered.clear();
        {
            for (unsigned i = 0; i < N; i++) {
                anss[ranges[i].id] = i;
                if (ranges[i].y != 0) anss[ranges[i].id] -= (unsigned)ys_ordered.order_of_key({N, ranges[i].y - 1});
                ys_ordered.insert({ranges[i].id, ranges[i].y});
            }
        }
        for (auto const &ans : anss) {
            std::cout << ans << ' ';
        }
        std::cout << '\n';
    }
}
