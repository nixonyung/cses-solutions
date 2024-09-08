#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Nearest%20Smaller%20Values.cpp>

    auto anss = std::vector<uint>(n);
    {
        auto inputs = std::vector<uint>(n);
        for (auto i : iota(0U, n)) {
            inputs[i] = read<uint>();

            uint ans = i - 1 // want the prev input
                       + 1;  // transform to 1-indexed input index, 0 means no smaller value
            while (ans > 0 && inputs[i] <= inputs[ans - 1]) {
                ans = anss[ans - 1]; // jump to nearest smaller value
            }
            anss[i] = ans;
        }
    }
    for (auto const &ans : anss) {
        std::cout << ans << ' ';
    }
    std::cout << '\n';
}