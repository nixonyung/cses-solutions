#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    auto min_num_stepss = std::vector<uint>(n + 1, std::numeric_limits<uint>::max());
    {
        // boundary condition
        min_num_stepss[0] = 0;

        for (auto num : iota(1U, n + 1)) {
            int i = num;
            while (i > 0) {
                if (min_num_stepss[num - i % 10] < std::numeric_limits<uint>::max()) {
                    min_num_stepss[num] = std::min(min_num_stepss[num], min_num_stepss[num - i % 10] + 1);
                }
                i /= 10;
            }
        }
    }
    std::cout << min_num_stepss[n] << '\n';
}