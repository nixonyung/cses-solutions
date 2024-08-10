#define VERSION_FENWICK_TREE 1
#define VERSION_ORDERED_SET 2

#define VERSION VERSION_FENWICK_TREE

#if VERSION == VERSION_FENWICK_TREE
#include <algorithm>
#include <cstdio>

// (ref.) [Fenwick Tree - Implementation](https://cp-algorithms.com/data_structures/fenwick.html#implementation)
template <size_t N>
struct FenwickTree {
    int vals[N];
    int n;

    FenwickTree(int n) {
        this->n = n;
        this->clear();
    }

    void clear() {
        std::fill_n(vals, n, 0);
    }

    void update(int pos, int delta) {
        for (; pos < n; pos = pos | (pos + 1)) {
            vals[pos] += delta;
        }
    }

    int prefix_sum(int pos) {
        int sum = 0;
        for (; pos >= 0; pos = (pos & (pos + 1)) - 1) {
            sum += vals[pos];
        }
        return sum;
    }
};

int main() {
    constexpr int MAX_N = (int)2e5;

    int n;
    scanf("%d", &n);

    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Nested%20Ranges%20Count.cpp> (main idea)
    // (ref.) <https://cses.fi/problemset/hack/2169/entry/7621796/> (optimization: using Structure of Arrays)

    int xs[MAX_N], ys[MAX_N];
    for (int i = 0; i < n; i++) {
        std::scanf("%d %d", &xs[i], &ys[i]);
    }

    int index_to_y_ordering[MAX_N];
    {
        int indexs_ordered_by_y[MAX_N];
        for (int i = 0; i < n; i++) {
            indexs_ordered_by_y[i] = i;
        }
        std::sort(
            indexs_ordered_by_y,
            indexs_ordered_by_y + n,
            [&ys](const auto &lhs, const auto &rhs) {
                return ys[lhs] < ys[rhs];
            }
        );

        int y_ordering = 0;
        index_to_y_ordering[indexs_ordered_by_y[0]] = y_ordering;
        for (int i = 1; i < n; i++) {
            if (ys[indexs_ordered_by_y[i]] > ys[indexs_ordered_by_y[i - 1]]) {
                y_ordering++;
            }
            index_to_y_ordering[indexs_ordered_by_y[i]] = y_ordering;
        }
    }

    int indexs[MAX_N];
    for (int i = 0; i < n; i++) {
        indexs[i] = i;
    }
    std::sort(
        indexs,
        indexs + n,
        [&xs, &ys](const auto &lhs, const auto &rhs) {
            return (xs[lhs] != xs[rhs]) ? xs[lhs] < xs[rhs]
                                        : ys[lhs] > ys[rhs];
        }
    );

    int ans[MAX_N];
    FenwickTree<MAX_N> tree(n);
    for (int i = n - 1; i >= 0; i--) {
        int y_ordering = index_to_y_ordering[indexs[i]];
        ans[indexs[i]] = tree.prefix_sum(y_ordering);
        tree.update(y_ordering, 1);
    }
    for (int i = 0; i < n; i++) {
        std::printf("%d ", ans[i]);
    }
    std::printf("\n");

    tree.clear();
    for (int i = 0; i < n; i++) {
        int y_ordering = index_to_y_ordering[indexs[i]];
        ans[indexs[i]] = i - tree.prefix_sum(y_ordering - 1);
        tree.update(y_ordering, 1);
    }
    for (int i = 0; i < n; i++) {
        std::printf("%d ", ans[i]);
    }
    std::printf("\n");
}
#elif VERSION == VERSION_ORDERED_SET
#include <algorithm>
#include <array>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template <typename T, typename CompareFn = std::less<>>
using ordered_set = __gnu_pbds::tree<
    T,
    __gnu_pbds::null_type,
    CompareFn,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;

struct Input {
    int x;
    int y;
    int index;
};

int main() {
    constexpr int MAX_N = (int)2e5;

    int n;
    std::scanf("%d", &n);

    // (ref.) [Counting Nested Ranges](https://stackoverflow.com/questions/78282577/counting-nested-ranges)

    Input inputs[MAX_N];
    for (int i = 0; i < n; i++) {
        std::scanf("%d %d", &inputs[i].x, &inputs[i].y);
        inputs[i].index = i;
    }

    std::sort(
        inputs,
        inputs + n,
        [](const auto &lhs, const auto &rhs) {
            return (lhs.x != rhs.x) ? (lhs.x < rhs.x)
                                    : (lhs.y > rhs.y);
        }
    );

    // solving the first line of outputs: how many other ranges a range contains
    int anss[MAX_N];
    // __gnu_pbds does not provide ordered_multiset, so use tuple as the element type to emulate uniqueness
    ordered_set<std::tuple<int, int>> ys; // ys[i] = {inputs[i].y, inputs[i].index}
    for (int i = n - 1; i >= 0; i--) {
        anss[inputs[i].index] = ys.order_of_key({inputs[i].y, n});
        ys.insert({inputs[i].y, inputs[i].index});
    }
    for (int i = 0; i < n; i++) {
        std::printf("%d ", anss[i]);
    }
    std::printf("\n");

    // solving the second line of outputs: how many other ranges contains the range
    ys.clear();
    for (int i = 0; i < n; i++) {
        anss[inputs[i].index] = i - ys.order_of_key({inputs[i].y, -1});
        ys.insert({inputs[i].y, inputs[i].index});
    }
    for (int i = 0; i < n; i++) {
        std::printf("%d ", anss[i]);
    }
    std::printf("\n");
}
#endif