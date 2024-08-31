#define VERSION_DIRECT_COMPUTATION 1
#define VERSION_INCREMENTAL 2

#define VERSION VERSION_INCREMENTAL

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = int();
    std::cin >> n;

#if VERSION == VERSION_DIRECT_COMPUTATION
    // (ref.) [Gray code](https://cp-algorithms.com/algebra/gray-code.html)
    for (auto i = 0; i < (1 << n); i++) {
        auto code = i ^ (i >> 1);

        for (auto j = n - 1; j >= 0; j--) {
            std::cout << ((code & (1 << j)) ? '1' : '0');
        }
        std::cout << '\n';
    }
#elif VERSION == VERSION_INCREMENTAL
    // (ref.) [Constructing an n-bit Gray code](https://omni.wikiwand.com/en/articles/Gray_code#Constructing_an_n-bit_Gray_code)
    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Introductory%20Problems/Gray%20Code.cpp>
    auto code = 0;
    for (auto i = 0; i < (1 << n); i++) {
        code ^= (i == 0) ? 0 : (1 << __builtin_ctz(i));

        for (auto j = n - 1; j >= 0; j--) {
            std::cout << ((code & (1 << j)) ? '1' : '0');
        }
        std::cout << '\n';
    }
#endif
}