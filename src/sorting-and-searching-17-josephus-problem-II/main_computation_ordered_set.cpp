#include "ordered_set.hpp"
#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto k = read<uint>();

    OrderedSet<int> childs;
    {
        for (auto i : iota(0U, n)) {
            childs.insert(i + 1);
        }
    }

    ulong pos = 0;
    for (auto _ : iota(0U, n)) {
        pos = (pos + k) % childs.size();
        auto it = childs.find_by_order(pos);
        std::cout << *it << ' ';
        childs.erase(it);
    }
    std::cout << '\n';
}