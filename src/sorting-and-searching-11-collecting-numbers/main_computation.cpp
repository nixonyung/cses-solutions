#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    auto poss = std::vector<uint>(n);
    for (auto i : iota(0U, n)) {
        poss[read<uint>()] = i;
    }

    // ans is the number of increasing subsequence in `pos`
    uint ans = 1;
    for (auto i : iota(1U, n)) {
        if (poss[i] > poss[i + 1]) {
            ans++;
        }
    }
    std::cout << ans << '\n';
}