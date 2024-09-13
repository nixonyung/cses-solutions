#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    ulong ans = 0;
    {
        int curr_max_x = 0;
        for (auto _ : iota(0U, n)) {
            auto x = read<int>();
            curr_max_x = std::max(curr_max_x, x);
            ans += curr_max_x - x;
        }
    }
    std::cout << ans << '\n';
}