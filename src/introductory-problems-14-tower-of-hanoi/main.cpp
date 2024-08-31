#define VERSION_ITERATIVE 1
#define VERSION_RECURSIVE 2
#define VERSION_DIRECT_COMPUTATION 3

#define VERSION VERSION_RECURSIVE

inline auto constexpr get_num_moves(int n) {
    /*
    consider the recursive solution, observe that:
        hanoi(1) = 1
        hanoi(2) = 1+2*hanoi(1) = 1+2     = 3
        hanoi(3) = 1+2*hanoi(2) = 1+2+4   = 7
        hanoi(4) = 1+2*hanoi(3) = 1+2+4+8 = 15
        ...
    we have hanoi(n) = 1+2*hanoi(n-1)+1 = sum_{k=1}^{n-1} 2^k = 2^n - 1
    */
    return (1 << n) - 1;
}

#if VERSION == VERSION_ITERATIVE
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = int();
    std::cin >> n;

    auto num_moves = get_num_moves(n);
    std::cout << num_moves << '\n';

    auto disk_poss = std::vector<int>(16, 0);
    auto peg_tops = std::vector<int>{0, n, n};

    // [Iterative solution](https://omni.wikiwand.com/en/articles/Tower_of_Hanoi#Iterative_solution)
    auto disk_zero_direction = (n & 1) ? -1 : 1;
    auto is_moving_disk_zero = true;
    while (num_moves--) {
        auto disk_to_move = int();
        auto target = int();
        if (is_moving_disk_zero) {
            disk_to_move = 0;
            target = (disk_poss[0] + disk_zero_direction + 3) % 3; // +3 to ensure positive target
        } else {
            // the movable non-zero disk must be the smaller one
            disk_to_move = n;
            for (auto i = 0; i < 3; i++) {
                if (peg_tops[i] != 0 && peg_tops[i] < disk_to_move) {
                    disk_to_move = peg_tops[i];
                }
            }
            target = 3 - disk_poss[0] - disk_poss[disk_to_move];
        }

        auto source = disk_poss[disk_to_move];
        disk_poss[disk_to_move] = target;
        peg_tops[target] = disk_to_move;
        // find the next disk under disk_to_move and update peg_tops[source]
        auto found = false;
        for (auto i = disk_to_move + 1; i < n; i++) {
            if (disk_poss[i] == source) {
                peg_tops[source] = i;
                found = true;
                break;
            }
        }
        if (!found) {
            peg_tops[source] = n;
        }

        std::cout << source + 1 << ' ' << target + 1 << '\n';
        is_moving_disk_zero = !is_moving_disk_zero;
    }
}
#elif VERSION == VERSION_RECURSIVE
#include <iostream>

// (ref.) [Recursive solution](https://omni.wikiwand.com/en/articles/Tower_of_Hanoi#Recursive_solution)
auto move_disks(
    int n,
    int source,
    int spare,
    int target
) {
    if (n == 1) {
        std::cout << source << ' ' << target << '\n';
        return;
    }

    move_disks(n - 1, source, target, spare);
    std::cout << source << ' ' << target << '\n';
    move_disks(n - 1, spare, source, target);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = int();
    std::cin >> n;

    std::cout << get_num_moves(n) << '\n';
    move_disks(n, 1, 2, 3);
}
#elif VERSION == VERSION_DIRECT_COMPUTATION
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = int();
    std::cin >> n;

    auto num_moves = get_num_moves(n);
    std::cout << num_moves << '\n';

    // (ref.) [Binary solution](https://omni.wikiwand.com/en/articles/Tower_of_Hanoi#Binary_solution)
    auto is_odd = bool(n & 1);
    for (auto i = 1; i <= num_moves; i++) {
        auto source = (i - (i & -i)) % 3;
        auto target = (i + (i & -i)) % 3;
        if (is_odd) {
            std::cout << source + 1
                      << ' '
                      << target + 1
                      << '\n';
        } else {
            std::cout << ((source == 0) ? 1 : (4 - source))
                      << ' '
                      << ((target == 0) ? 1 : (4 - target))
                      << '\n';
        }
    }
}
#endif