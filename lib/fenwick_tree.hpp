#ifndef __FENWICK_TREE_H
#define __FENWICK_TREE_H

#include <algorithm>
#include <utility>
#include <vector>

template <
    typename T,
    typename SumFn = std::plus<>>
    requires std::regular_invocable<SumFn, T, T> &&
             std::same_as<T, std::invoke_result_t<SumFn, T, T>>
struct FenwickTree {
    using container_type = std::vector<T>;
    using size_type = container_type::size_type;

    // (ref.) [Fenwick tree](https://www.wikiwand.com/en/articles/Fenwick_tree)
    // (ref.) [Fenwick Tree - Implementation](https://cp-algorithms.com/data_structures/fenwick.html#implementation)

    FenwickTree(size_type n)
        : c(n),
          sum_fn() {
        this->clear();
    }

    // expose values and container const methods, e.g. size() and capacity()
    auto const &data() const { return c; }

    auto clear() -> void {
        std::ranges::fill(c, 0);
    }

    auto update_at(size_type pos, T delta) -> void {
        for (long i = pos; std::cmp_less(i, c.size()); i = next_update_pos(i)) {
            c[i] = sum_fn(c[i], delta);
        }
    }

    auto prefix_sum(size_type pos) const -> T {
        T ans = {};
        {
            long i = pos;
            // if pos >= n, skip until pos < n, effectively the same as right-padding data with zeroes
            while (std::cmp_greater_equal(i, c.size())) {
                i = next_interrogate_pos(i);
            }
            for (long i = pos; i >= 0; i = next_interrogate_pos(i)) {
                ans = sum_fn(ans, c[i]);
            }
        }
        return ans;
    }

  private:
    static inline constexpr auto next_update_pos = [](auto i) { return i | (i + 1); };
    static inline constexpr auto next_interrogate_pos = [](auto i) { return (i & (i + 1)) - 1; };

    container_type c;
    SumFn sum_fn;
};

#endif