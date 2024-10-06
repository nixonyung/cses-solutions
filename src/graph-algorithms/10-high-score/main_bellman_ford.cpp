/*
DFS-based algorithms won't be efficient:
- DFS
  => not guaranteed to detect positive cycles in the search paths
- DFS to find all positive cycles first
  => not guaranteed to detect positive sub-cycles in the detected cycles

=> we need a DP-based algorithm

(ref.) [Bellman-Ford Algorithm](https://cp-algorithms.com/graph/bellman_ford.html)
The algorithm is modified to accomplish the following tasks at the same time:
- find the LONGEST path from `start` with POSITIVE cycle detection
- for all `rooms`, check if it can reach to the `end`
*/

#include <bitset>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>

// custom primitive data types
typedef unsigned int uint;
typedef unsigned long ulong;
typedef std::size_t usize;
typedef std::make_signed_t<std::size_t> isize;

namespace {
struct Tunnel {
    uint start;
    uint end;
    int score;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const uint MAX_NUM_ROOMS = 2500;

    uint num_rooms;
    uint num_tunnels;
    {
        std::cin >> num_rooms >> num_tunnels;
    }

    auto tunnels = std::vector<Tunnel>(num_tunnels);
    {
        for (uint i = 0; i < num_tunnels; i++) {
            std::cin >> tunnels[i].start >> tunnels[i].end >> tunnels[i].score;
            // transform to 0-indexed (personal preference)
            tunnels[i].start--;
            tunnels[i].end--;
        }
    }

    auto max_scores = std::vector<long>(num_rooms, LONG_MIN);
    auto can_reach_ends = std::vector<bool>(num_rooms, false);
    auto max_score_updateds = std::bitset<MAX_NUM_ROOMS>(); // optimization: SPFA
    auto next_max_score_updateds = std::bitset<MAX_NUM_ROOMS>();
    {
        max_scores[0] = 0;
        max_score_updateds[0] = true;
        can_reach_ends[num_rooms - 1] = true;

        for (uint epoch = 0; epoch < num_rooms; epoch++) {
            next_max_score_updateds.reset();
            for (auto const &[start, end, score] : tunnels) {
                if (can_reach_ends[end]) {
                    can_reach_ends[start] = true;
                }

                if (
                    max_score_updateds[start] &&
                    max_scores[start] + score > max_scores[end]
                ) {
                    if (epoch + 1 == num_rooms && can_reach_ends[end]) {
                        std::cout << "-1\n";
                        std::exit(0);
                    }
                    max_scores[end] = max_scores[start] + score;
                    next_max_score_updateds[end] = true;
                }
            }
            if (next_max_score_updateds.none()) break;
            max_score_updateds = next_max_score_updateds;
        }
    }
    std::cout << max_scores[num_rooms - 1] << '\n';
}