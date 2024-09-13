#include "ordered_set.hpp"
#include "utils.hpp"

namespace {
struct Input {
    uint id;
    uint val;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto k = read<uint>();

    // (ref.) [CSES - Sliding Median - Solution 3](https://usaco.guide/problems/cses-1076-sliding-median/solution#solution-3-order-statistic-tree)

    {
        auto values = std::vector<uint>(n);
        auto inputs_ordered = OrderedSet<
            Input,
            decltype([](auto const &lhs, auto const &rhs) {
                return (lhs.val != rhs.val) ? (lhs.val < rhs.val)
                                            : (lhs.id < rhs.id);
            })>();
        {
            for (auto i : iota(0U, k)) {
                values[i] = read<uint>();
                inputs_ordered.insert({i, values[i]});
            }
            std::cout << inputs_ordered.find_by_order((k - 1) >> 1)->val << ' ';
        }
        {
            for (auto i : iota(k, n)) {
                values[i] = read<uint>();
                inputs_ordered.erase(inputs_ordered.lower_bound({0, values[i - k]}));
                inputs_ordered.insert({i, values[i]});
                std::cout << inputs_ordered.find_by_order((k - 1) >> 1)->val << ' ';
            }
        }
    }
    std::cout << '\n';
}