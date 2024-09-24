#ifndef __DISJOINT_SET_UNION_H
#define __DISJOINT_SET_UNION_H

#include <concepts>
#include <vector>

// (ref.) [Disjoint Set Union](https://cp-algorithms.com/data_structures/disjoint_set_union.html)
template <typename Size>
    requires std::unsigned_integral<Size>
struct DisjointSetUnion {
    struct Node {
        Size root;
        Size size;
    };

    DisjointSetUnion(Size n)
        : nodes(n),
          _num_roots(n) {
        for (Size i = 0; i < n; i++) {
            nodes[i] = {i, 1};
        }
    }

    auto num_roots() -> Size const & { return _num_roots; }
    auto root_id(Size id) -> Size {
        return (id == nodes[id].root) ? id
                                      : (nodes[id].root = root_id(nodes[id].root));
    }
    auto is_connected(Size id1, Size id2) -> bool { return root_id(id1) == root_id(id2); }

    auto connect(Size id1, Size id2) -> void {
        if (is_connected(id1, id2)) {
            return;
        }
        auto root_id1 = root_id(id1);
        auto root_id2 = root_id(id2);
        // put root with smaller size under the root with larger size
        if (nodes[root_id1].size >= nodes[root_id2].size) {
            nodes[root_id2].root = root_id1;
            nodes[root_id1].size += nodes[root_id2].size;
        } else {
            nodes[root_id1].root = root_id2;
            nodes[root_id2].size += nodes[root_id1].size;
        }
        _num_roots--;
    }

  private:
    std::vector<Node> nodes;
    Size _num_roots;
};

#endif