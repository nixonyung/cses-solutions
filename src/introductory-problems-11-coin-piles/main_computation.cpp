#include "utils.hpp"

int main() {
    enable_fast_io();

    auto num_tests = read<uint>();
    while (num_tests--) {
        auto num1 = read<uint>();
        auto num2 = read<uint>();

        // as each move remove 3 coins, for cases where all coins can be removed,
        // the total number of coins must be a multiple of 3
        if ((num1 + num2) % 3) {
            std::cout << "NO\n";
            continue;
        }
        // there exists a solution iff the size of the larger pile is at most twice the size of the smaller pile
        if ((num1 > num2 * 2) || (num2 > num1 * 2)) {
            std::cout << "NO\n";
            continue;
        }
        std::cout << "YES\n";
    }
}