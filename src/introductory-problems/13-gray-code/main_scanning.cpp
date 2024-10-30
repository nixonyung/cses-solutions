// (ref.) [Constructing an n-bit Gray code](https://wikiwand.com/en/articles/Gray_code#Constructing_an_n-bit_Gray_code)
// (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Introductory%20Problems/Gray%20Code.cpp>

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    unsigned code;
    for (unsigned i = 0; i < 1U << N; i++) {
        code = (i == 0) ? 0 : code ^ (1U << std::countr_zero(i));

        for (unsigned j = 0; j < N; j++) {
            std::cout << ((code & (1U << (N - 1 - j))) > 0);
        }
        std::cout << '\n';
    }
}