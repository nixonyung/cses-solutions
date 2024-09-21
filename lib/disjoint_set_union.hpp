#ifndef __DISJOINT_SET_UNION_H
#define __DISJOINT_SET_UNION_H

#include <concepts>
#include <ranges>
#include <vector>

template <typename T>
    requires std::unsigned_integral<T>
struct DisjointSetUnion {
    using container_type = std::vector<T>;

    // (ref.) [Disjoint Set Union](https://cp-algorithms.com/data_structures/disjoint_set_union.html)

    DisjointSetUnion(T n)
        : c(n),
          num_parents(n) {
        for (auto const &i : std::views::iota(0U, n)) {
            c[i] = i;
        }
    }

    auto get_num_parents() -> T { return num_parents; }

    auto parent(T node) -> T {
        if (node == c[node]) {
            return node;
        }
        return c[node] = parent(c[node]);
    }

    auto connect(T node1, T node2) -> void {
        node1 = parent(node1);
        node2 = parent(node2);
        // common parent is the smaller parent
        if (node1 > node2) {
            std::swap(node1, node2);
        }
        if (node1 != node2) {
            c[node2] = node1;
            num_parents--;
        }
    }

  private:
    container_type c;
    T num_parents;
};

#endif