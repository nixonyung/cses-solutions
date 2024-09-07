#include "fenwick_tree.hpp"
#include "utils.hpp"

namespace {
struct Input {
    uint id;
    uint x;
    uint y;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Nested%20Ranges%20Count.cpp>
    // (ref.) <https://cses.fi/problemset/hack/2169/entry/7621796/>

    auto inputs = std::vector<Input>(n);
    {
        for (uint i = 0; auto &input : inputs) {
            input = {i++, read<uint>(), read<uint>()};
        }
    }

    auto id_to_y_order = find_order_of_elements(
        inputs,
        [](auto const &input) { return input.y; }
    );
    std::ranges::sort(
        inputs,
        [](auto const &lhs, auto const &rhs) {
            return (lhs.x != rhs.x) ? (lhs.x < rhs.x)
                                    : (lhs.y > rhs.y);
        }
    );

    auto anss = std::vector<std::size_t>(n);
    {
        auto tree = FenwickTree<std::size_t>(n);
        {
            for (auto const &input : inputs | std::views::reverse) {
                anss[input.id] = tree.prefix_sum(id_to_y_order[input.id]);
                tree.update_at(id_to_y_order[input.id], 1);
            }
        }
        for (auto const &ans : anss) {
            std::cout << ans << ' ';
        }
        std::cout << '\n';

        tree.clear();
        {
            for (uint i = 0; auto const &input : inputs) {
                anss[input.id] = (i++) - tree.prefix_sum(id_to_y_order[input.id] - 1);
                tree.update_at(id_to_y_order[input.id], 1);
            }
        }
        for (auto const &ans : anss) {
            std::cout << ans << ' ';
        }
        std::cout << '\n';
    }
}
