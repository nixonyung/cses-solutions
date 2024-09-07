#include "utils.hpp"
#include <unordered_map>

int main() {
    enable_fast_io();

    auto n = read<uint>();

    uint max_unique_len = 0;
    {
        auto input_to_pos = std::unordered_map<uint, uint>(n);
        uint unique_start = 0;
        for (auto i : iota(0U, n)) {
            auto input = read<uint>();
            if (input_to_pos.contains(input)) {
                max_unique_len = std::max(max_unique_len, i - unique_start);
                unique_start = std::max(unique_start, input_to_pos[input] + 1);
            }
            input_to_pos[input] = i;
        }
        max_unique_len = std::max(max_unique_len, n - unique_start);
    }
    std::cout << max_unique_len << '\n';
}