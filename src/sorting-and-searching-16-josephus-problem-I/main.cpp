#include "../../lib/cses_io.hpp"
#include <iterator>
#include <list>

int main() {
    auto const K = 2; // choosing every 2 children

    cses::enable_fast_io();

    auto n = cses::read<int>();

    // solve by simulation

    // using std::list as it supports O(1) deletion
    auto childs = std::list<int>(n);
    for (int i = 1; auto &child : childs) {
        child = i;
        i++;
    }

    auto child_idx = 0;
    auto it = childs.begin();
    while (!childs.empty()) {
        child_idx += K - 1;
        if (child_idx >= childs.size()) {
            child_idx %= childs.size();
            it = std::next(childs.begin(), child_idx);
        } else {
            std::advance(it, K - 1);
        }

        std::cout << *it << ' ';
        it = childs.erase(it); // childs.erase invalidates `it`, and return the new iterator after the erased element
    }
    std::cout << '\n';
}
