#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    auto num_moves = (1U << n) - 1;
    std::cout << num_moves << '\n';

    // [Iterative solution](https://omni.wikiwand.com/en/articles/Tower_of_Hanoi#Iterative_solution)

    auto disk_poss = std::vector<uint>(16, 0);
    auto peg_tops = std::vector<uint>{0, n, n};
    int disk_zero_direction = (n & 1) ? -1 : 1;
    for (auto i : iota(1U, (uint)num_moves + 1)) {
        uint disk_to_move;
        uint target;
        if (i & 1) {
            disk_to_move = 0;
            target = (disk_poss[0] + disk_zero_direction + 3) % 3; // +3 to ensure target is positive
        } else {
            disk_to_move = std::countr_zero(i);
            target = 3 - disk_poss[0] - disk_poss[disk_to_move]; // the peg without disk_to_move and disk 0 (because no disk can be put above disk 0)
        }

        auto source = disk_poss[disk_to_move];
        disk_poss[disk_to_move] = target;
        peg_tops[target] = disk_to_move;
        {
            // find the next disk under disk_to_move and update peg_tops[source]
            bool found = false;
            for (auto i : iota(disk_to_move + 1, n)) {
                if (disk_poss[i] == source) {
                    peg_tops[source] = i;
                    found = true;
                    break;
                }
            }
            if (!found) {
                peg_tops[source] = n;
            }
        }

        std::cout << source + 1 << ' ' << target + 1 << '\n';
    }
}
