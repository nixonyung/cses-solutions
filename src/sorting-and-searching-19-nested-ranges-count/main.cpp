#define VERSION_FENWICK_TREE 1
#define VERSION_ORDERED_SET 2

#define VERSION VERSION_FENWICK_TREE

#include "../../lib/cses_io.hpp"
#if VERSION == VERSION_FENWICK_TREE
#include "../../lib/fenwick_tree.hpp"
#include "../../lib/utils.hpp"
#elif VERSION == VERSION_ORDERED_SET
#include "../../lib/ordered_set.hpp"
#endif
#include <algorithm>
#include <iostream>

struct Input {
    std::size_t x;
    std::size_t y;

    friend std::istream &operator>>(std::istream &in, Input &input) {
        return in >> input.x >> input.y;
    }
};

int main() {
    cses::enable_fast_io();

    auto n = cses::read<int>();

    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Nested%20Ranges%20Count.cpp>
    // (ref.) <https://cses.fi/problemset/hack/2169/entry/7621796/>

    auto inputs = cses::read_vector_with_ids<Input>(n);

#if VERSION == VERSION_FENWICK_TREE
    auto id_to_y_order = order_of_elements(
        inputs,
        [](auto const &input) { return input.val.y; }
    );
#endif

    std::ranges::sort(
        inputs,
        [](auto const &lhs, auto const &rhs) {
            return (lhs.val.x != rhs.val.x) ? (lhs.val.x < rhs.val.x)
                                            : (lhs.val.y > rhs.val.y);
        }
    );

    auto anss = std::vector<std::size_t>(n);

#if VERSION == VERSION_FENWICK_TREE
    auto tree = FenwickTree<std::size_t>(n);

    for (int i = n - 1; i >= 0; i--) {
        anss[inputs[i].id] = tree.prefix_sum(id_to_y_order[inputs[i].id]);
        tree.update_at(id_to_y_order[inputs[i].id], 1);
    }
    cses::print_range(anss);

    tree.clear();

    for (int i = 0; i < n; i++) {
        anss[inputs[i].id] = i - tree.prefix_sum(id_to_y_order[inputs[i].id] - 1);
        tree.update_at(id_to_y_order[inputs[i].id], 1);
    }
    cses::print_range(anss);
#elif VERSION == VERSION_ORDERED_SET
    // __gnu_pbds does not provide ordered_multiset, so use tuple as the element type to ensure uniqueness of each `y`
    auto ys_ordered = OrderedSet<std::tuple<std::size_t, std::make_signed_t<std::size_t>>>(); // ys_ordered[i] = {inputs[i].val.y, inputs[i].id}

    for (int i = n - 1; i >= 0; i--) {
        anss[inputs[i].id] = ys_ordered.order_of_key({inputs[i].val.y, n});
        ys_ordered.insert({inputs[i].val.y, inputs[i].id});
    }
    cses::print_range(anss);

    ys_ordered.clear();

    for (int i = 0; i < n; i++) {
        anss[inputs[i].id] = i - ys_ordered.order_of_key({inputs[i].val.y, -1});
        ys_ordered.insert({inputs[i].val.y, inputs[i].id});
    }
    cses::print_range(anss);
#endif
}
