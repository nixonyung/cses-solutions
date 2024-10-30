#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned long N;
    {
        std::cin >> N;
    }

    std::cout << N << ' ';
    while (N != 1) {
        N = (N & 1) ? N * 3 + 1 : N >> 1;
        std::cout << N << ' ';
    }
    std::cout << '\n';
}