#include "utils.hpp"
#include <map>

// correct implementation but outputs are different from tests
int main() {
    enable_fast_io();

    auto n = read<uint>();
    if (n == 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    auto target = read<uint>();

    auto input_to_id = std::map<uint, uint>();
    {
        for (auto i : iota(0U, n)) {
            auto input = read<uint>();
            if (input_to_id.contains(target - input)) {
                std::cout << i + 1 << ' ' << input_to_id[target - input] << '\n';
                return 0;
            }
            input_to_id[input] = i + 1;
        }
    }
    std::cout << "IMPOSSIBLE\n";
}
