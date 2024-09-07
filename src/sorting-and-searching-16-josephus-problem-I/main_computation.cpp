#include "utils.hpp"
#include <list>

int main() {
    const uint K = 2; // choosing every 2 children

    enable_fast_io();

    auto n = read<uint>();

    // solve by simulation

    // using std::list as it supports O(1) deletion
    auto childs = std::list<uint>(n);
    for (auto it = childs.begin(); auto i : iota(0U, n)) {
        *(it++) = i + 1;
    }

    ulong pos = 0;
    auto it = childs.begin();
    while (!childs.empty()) {
        pos += K - 1;
        if (pos >= childs.size()) {
            pos %= childs.size();
            it = std::next(childs.begin(), pos);
        } else {
            std::advance(it, K - 1);
        }

        std::cout << *it << ' ';
        it = childs.erase(it); // childs.erase invalidates `it`, and return the new iterator after the erased element
    }
    std::cout << '\n';
}
