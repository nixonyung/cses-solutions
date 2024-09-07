#include "utils.hpp"
#include <set>

int main() {
    enable_fast_io();

    auto n = read<uint>();

    auto s = std::set<uint>();
    for (auto _ : iota(0U, n)) {
        s.insert(read<uint>());
    }
    std::cout << s.size() << '\n';
}