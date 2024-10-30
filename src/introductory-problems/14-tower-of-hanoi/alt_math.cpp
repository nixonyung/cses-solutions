// (ref.) [Binary solution](https://wikiwand.com/en/articles/Tower_of_Hanoi#Binary_solution)

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }
    unsigned const num_moves = (1U << N) - 1;
    std::cout << num_moves << '\n';

    for (unsigned i = 1; i <= num_moves; i++) {
        unsigned const source = (i - (i & -i)) % 3;
        unsigned const target = (i + (i & -i)) % 3;
        if (N & 1) {
            std::cout << source + 1
                      << ' '
                      << target + 1
                      << '\n';
        } else {
            std::cout << ((source == 0) ? 0 : (3 - source)) + 1
                      << ' '
                      << ((target == 0) ? 0 : (3 - target)) + 1
                      << '\n';
        }
    }
}