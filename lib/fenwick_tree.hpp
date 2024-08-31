#ifndef __FENWICK_TREE_H
#define __FENWICK_TREE_H

#include "utils.hpp"
#include <algorithm>
#include <vector>

template <
    typename T,
    typename SumFn = std::plus<T>>
    requires regular_invocable_returning<T, SumFn, T, T>
struct FenwickTree {
    using container_type = std::vector<T>;
    using size_type = container_type::size_type;
    using position_type = std::make_signed_t<size_type>; // allowing position to be negative is more convenient when computing next_update_pos and next_interrogate_pos

    // (ref.) [Fenwick tree](https://www.wikiwand.com/en/articles/Fenwick_tree)
    // (ref.) [Fenwick Tree - Implementation](https://cp-algorithms.com/data_structures/fenwick.html#implementation)

    FenwickTree(size_type n)
        : c(n),
          sum_fn() {
        this->clear();
    }

    auto const &data() const { return c; }

    auto clear() -> void {
        std::ranges::fill(c, 0);
    }

    auto update_at(position_type pos, T delta) -> void {
        for (; pos < position_type(c.size()); pos = next_update_pos(pos)) {
            c[pos] = sum_fn(c[pos], delta);
        }
    }

    auto prefix_sum(position_type pos) const -> T {
        auto ans = T();
        // if pos < 0, do not sum any elements
        if (pos >= 0) {
            // if pos >= n, skip until pos < n, effectively the same as padding data with zeroes
            while (pos >= position_type(c.size())) {
                pos = next_interrogate_pos(pos);
            }
            while (pos >= 0) {
                ans = sum_fn(ans, c[pos]);
                pos = next_interrogate_pos(pos);
            }
        }
        return ans;
    }

  private:
    static auto constexpr next_update_pos(position_type pos) { return pos | (pos + 1); }
    static auto constexpr next_interrogate_pos(position_type pos) { return (pos & (pos + 1)) - 1; }

    container_type c;
    SumFn          sum_fn;
};

#endif