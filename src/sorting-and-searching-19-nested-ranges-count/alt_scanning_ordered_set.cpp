#include "ordered_set.hpp"
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

        std::ranges::sort(
            inputs,
            [](auto const &lhs, auto const &rhs) {
                return (lhs.x != rhs.x) ? (lhs.x < rhs.x)
                                        : (lhs.y > rhs.y);
            }
        );
    }

    auto anss = std::vector<std::size_t>(n);
    {
        // __gnu_pbds does not provide ordered_multiset, so use tuple as the element type to ensure uniqueness of each `y`
        auto ys_ordered = OrderedSet<std::tuple<std::size_t, std::make_signed_t<std::size_t>>>(); // ys_ordered[i] = {inputs[i].val.y, inputs[i].id}
        {
            for (auto const &input : inputs | std::views::reverse) {
                anss[input.id] = ys_ordered.order_of_key({input.y, n});
                ys_ordered.insert({input.y, input.id});
            }
            for (auto const &ans : anss) {
                std::cout << ans << ' ';
            }
            std::cout << '\n';
        }

        ys_ordered.clear();
        {
            for (uint i = 0; auto const &input : inputs) {
                anss[input.id] = (i++) - ys_ordered.order_of_key({input.y, -1});
                ys_ordered.insert({input.y, input.id});
            }
            for (auto const &ans : anss) {
                std::cout << ans << ' ';
            }
            std::cout << '\n';
        }
    }
}
