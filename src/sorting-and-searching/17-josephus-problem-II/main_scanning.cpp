#include "ordered_set.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned K;
    {
        std::cin >> N >> K;
    }

    OrderedSet<unsigned> childs;
    {
        for (decltype(childs)::value_type i = 0; i < N; i++) {
            childs.insert(i + 1);
        }
    }

    {
        unsigned long pos = 0;
        for (unsigned i = 0; i < N; i++) {
            pos = (pos + K) % childs.size();
            auto it = childs.find_by_order(pos);
            std::cout << *it << ' ';
            childs.erase(it);
        }
    }
    std::cout << '\n';
}