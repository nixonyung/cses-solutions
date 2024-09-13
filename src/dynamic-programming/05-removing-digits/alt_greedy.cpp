#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    uint min_num_steps = 0;
    {
        while (n > 0) {
            uint max_digit = 0;
            {
                uint i = n;
                while (i > 0) {
                    max_digit = std::max(max_digit, i % 10);
                    i /= 10;
                }
            }
            n -= max_digit;
            min_num_steps++;
        }
    }
    std::cout << min_num_steps << '\n';
}