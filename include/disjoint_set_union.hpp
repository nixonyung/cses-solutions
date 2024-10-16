#ifndef __DISJOINT_SET_UNION_H
#define __DISJOINT_SET_UNION_H

#include <stack>
#include <utility>
#include <vector>

// (ref.) [Disjoint Set Union](https://cp-algorithms.com/data_structures/disjoint_set_union.html)
struct DisjointSetUnion {
    struct Node {
        size_t next;
        size_t num_descendants; // includes the node itself
    };

    DisjointSetUnion(size_t n) : nodes(n), _num_roots(n) {
        for (size_t i = 0; i < n; i++) nodes[i] = {i, 1};
    }

    auto num_roots() const -> size_t { return _num_roots; }
    auto root(size_t id) -> size_t {
        // return `id`'s root, also lazily update `next`s to root along the path from `id` to the root

        /*
        no updates are needed for the following cases:
        - id is a root
          i.e. id is pointing to itself
          i.e. "nodes[id].next == id", which trivially implies "nodes[ nodes[id].next ].next == nodes[id].next"
                                                                       --------------
                                                                           == id
        - id's next is a root
          i.e. id's next is pointing to itself
          i.e. "nodes[nodes[id].next].next == nodes[id].next"
        */
        if (nodes[id].next != nodes[nodes[id].next].next) {
            static auto to_visits = std::stack<size_t>();
            static auto in_paths = std::vector<bool>(nodes.size(), false);

            to_visits.push(id);
            while (!to_visits.empty()) {
                auto const curr = to_visits.top();
                to_visits.pop();

                auto const root = nodes[curr].next;
                if (root == curr) continue;

                if (in_paths[curr]) {
                    in_paths[curr] = false;
                    nodes[curr].next = nodes[root].next;
                } else {
                    in_paths[curr] = true;
                    to_visits.push(curr);
                    to_visits.push(root);
                }
            }
        }
        return nodes[id].next;
    }
    auto is_connected(size_t id1, size_t id2) -> bool { return root(id1) == root(id2); }

    auto connect(size_t id1, size_t id2) -> Node const & {
        auto root1 = root(id1);
        auto root2 = root(id2);
        if (root1 != root2) {
            // put root with smaller size under the root with larger size
            if (nodes[root1].num_descendants < nodes[root2].num_descendants) std::swap(root1, root2);
            nodes[root2].next = root1;
            nodes[root1].num_descendants += nodes[root2].num_descendants;
            _num_roots--;
        }
        return nodes[root1];
    }

  private:
    std::vector<Node> nodes;
    size_t _num_roots;
};

#endif