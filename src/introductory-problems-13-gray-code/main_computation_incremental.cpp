#include "utils.hpp"
#include <format>

int main() {
    enable_fast_io();

    auto n = read<size_t>();

    // (ref.) [Constructing an n-bit Gray code](https://omni.wikiwand.com/en/articles/Gray_code#Constructing_an_n-bit_Gray_code)
    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Introductory%20Problems/Gray%20Code.cpp>

    uint code = 0;
    for (auto i : iota(0U, 1U << n)) {
        code ^= (i == 0) ? 0 : (1U << std::countr_zero(i));
        std::cout << std::format("{:0{}b}", code, n) << '\n';
    }
}