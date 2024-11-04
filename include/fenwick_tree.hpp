#ifndef __FENWICK_TREE_H
#define __FENWICK_TREE_H

// (ref.) [Fenwick tree](https://www.wikiwand.com/en/articles/Fenwick_tree)
// (ref.) [Fenwick Tree - Implementation](https://cp-algorithms.com/data_structures/fenwick.html#implementation)

#include <concepts>
#include <vector>

template <
    typename T,
    typename SumFn = std::plus<>>
    requires std::regular_invocable<SumFn, T, T> &&
             std::same_as<T, std::invoke_result_t<SumFn, T, T>>
struct FenwickTree {
    FenwickTree(size_t n) : c(n), sum_fn{} {
        clear();
    }

    auto const size() const { return c.size(); }
    auto clear() -> void { c.assign(c.size(), 0); }

    void update_at(size_t pos, T delta) {
        for (; pos < size(); pos = next_update_pos(pos)) c[pos] = sum_fn(c[pos], delta);
    }

    T prefix_sum(size_t pos) const {
        T ans = {};
        while (pos >= c.size()) pos = next_interrogate_pos(pos);
        for (; pos < c.size(); pos = next_interrogate_pos(pos)) ans = sum_fn(ans, c[pos]);
        return ans;
    }

  private:
    static inline size_t next_update_pos(size_t i) { return i | (i + 1); };
    static inline size_t next_interrogate_pos(size_t i) { return (i & (i + 1)) - 1; };

    std::vector<T> c;
    SumFn sum_fn;
};

#endif