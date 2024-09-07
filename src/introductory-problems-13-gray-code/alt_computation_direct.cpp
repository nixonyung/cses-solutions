#include "utils.hpp"
#include <format>

int main() {
    enable_fast_io();

    auto n = read<size_t>();

    // (ref.) [Gray code](https://cp-algorithms.com/algebra/gray-code.html)

    for (auto i : iota(0U, 1U << n)) {
        auto code = i ^ (i >> 1);
        std::cout << std::format("{:0{}b}", code, n) << '\n';
    }
}