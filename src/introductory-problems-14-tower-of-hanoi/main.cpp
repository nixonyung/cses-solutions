#define VERSION_ITERATIVE 1
#define VERSION_RECURSIVE 2
#define VERSION_DIRECT_COMPUTATION 3

#define VERSION VERSION_RECURSIVE

#include <cstdio>

inline int get_num_moves(int n) {
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
int main() {
    int n;
    scanf("%d", &n);

    int num_moves = get_num_moves(n);
    printf("%d\n", num_moves);

    int disk_poss[16];
    for (int i = 0; i < n; i++) {
        disk_poss[i] = 0;
    }
    int peg_tops[3] = {0, n, n};

    // [Iterative solution](https://omni.wikiwand.com/en/articles/Tower_of_Hanoi#Iterative_solution)
    int disk_zero_direction = (n & 1) ? -1 : 1;
    bool is_moving_disk_zero = true;
    while (num_moves--) {
        int disk_to_move;
        int target;
        if (is_moving_disk_zero) {
            disk_to_move = 0;
            target = (disk_poss[0] + disk_zero_direction + 3) % 3;
        } else {
            // the movable non-zero disk must be the smaller one
            disk_to_move = n;
            for (int i = 0; i < 3; i++) {
                if (peg_tops[i] != 0 && peg_tops[i] < disk_to_move) {
                    disk_to_move = peg_tops[i];
                }
            }
            target = 3 - disk_poss[0] - disk_poss[disk_to_move];
        }

        int source = disk_poss[disk_to_move];
        disk_poss[disk_to_move] = target;
        peg_tops[target] = disk_to_move;
        // find the next disk under disk_to_move and update peg_tops[source]
        bool found = false;
        for (int i = disk_to_move + 1; i < n; i++) {
            if (disk_poss[i] == source) {
                peg_tops[source] = i;
                found = true;
                break;
            }
        }
        if (!found) {
            peg_tops[source] = n;
        }

        printf("%d %d\n", source + 1, target + 1);
        is_moving_disk_zero = !is_moving_disk_zero;
    }
}
#elif VERSION == VERSION_RECURSIVE
// (ref.) [Recursive solution](https://omni.wikiwand.com/en/articles/Tower_of_Hanoi#Recursive_solution)
void move(int n, int source, int spare, int target) {
    if (n == 1) {
        printf("%d %d\n", source, target);
        return;
    }
    move(n - 1, source, target, spare);
    printf("%d %d\n", source, target);
    move(n - 1, spare, source, target);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", get_num_moves(n));

    move(n, 1, 2, 3);
}
#elif VERSION == VERSION_DIRECT_COMPUTATION
int main() {
    int n;
    scanf("%d", &n);
    int num_moves = get_num_moves(n);
    printf("%d\n", num_moves);

    // (ref.) [Binary solution](https://omni.wikiwand.com/en/articles/Tower_of_Hanoi#Binary_solution)
    bool is_odd = n & 1;
    for (int i = 1; i <= num_moves; i++) {
        int source = (i - (i & -i)) % 3;
        int target = (i + (i & -i)) % 3;
        if (is_odd) {
            printf("%d %d\n", source + 1, target + 1);
        } else {
            printf("%d %d\n", (source == 0) ? 1 : (4 - source), (target == 0) ? 1 : (4 - target));
        }
    }
}
#endif