// (ref.) [CSES Solutions - Two Knights](https://www.geeksforgeeks.org/cses-solutions-two-knights/)

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    for (unsigned board_size = 1; board_size <= N; board_size++) {
        std::cout << (
                         // total number of configurations: choose any 2 cells from the board, order doesn't matter
                         (unsigned long)(board_size * board_size) * ((board_size * board_size) - 1) / 2 -
                         // total number of invalid configurations: two for each 2x3 and 3x2 cells
                         (unsigned long)((board_size - 1) * (board_size - 2) * 2) * 2
                     )
                  << '\n';
    }
}