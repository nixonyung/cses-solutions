// (ref.) [Gray code](https://cp-algorithms.com/algebra/gray-code.html)

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    for (unsigned i = 0; i < 1U << N; i++) {
        unsigned const code = i ^ (i >> 1);

        for (unsigned j = 0; j < N; j++) {
            std::cout << ((code & (1U << (N - 1 - j))) > 0);
        }
        std::cout << '\n';
    }
}