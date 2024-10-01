/*
DFS-esque Algorithms are not efficient:
- DFS
  => not guaranteed to detect positive cycles in the search paths
- DFS to find all positive cycles first
  => not guaranteed to detect positive sub-cycles in the detected cycles

solution: modified Bellman-Ford to find the LONGEST path with POSITIVE cycle detection
(ref.) [Bellman-Ford Algorithm](https://cp-algorithms.com/graph/bellman_ford.html)
*/

#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

// custom primitive data types
typedef unsigned int uint;
typedef unsigned long ulong;
typedef std::size_t usize;
typedef std::make_signed_t<std::size_t> isize;

namespace {
struct Tunnel {
    uint end_room_id;
    int score;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint num_rooms;
    uint num_tunnels;
    {
        std::cin >> num_rooms >> num_tunnels;
    }

    auto adjss = std::vector<std::vector<Tunnel>>(num_rooms);
    {
        uint start;
        uint end;
        int score;
        for (uint i = 0; i < num_tunnels; i++) {
            std::cin >> start >> end >> score;
            // transform to 0-indexed (personal preference)
            start--;
            end--;
            adjss[start].push_back({end, score});
        }
    }

    auto max_scores = std::vector<long>(num_rooms, LONG_MIN);
    auto updated_rooms_in_last_epoch = std::vector<uint>();
    {
        max_scores[0] = 0;

        struct ToVisit {
            uint epoch;
            uint room_id;
        };
        auto to_visits = std::queue<ToVisit>();
        to_visits.push({0, 0});
        while (!to_visits.empty()) {
            auto const [epoch, curr_room] = to_visits.front();
            to_visits.pop();

            for (auto const &[adj, score] : adjss[curr_room]) {
                if (max_scores[curr_room] + score <= max_scores[adj]) continue;
                max_scores[adj] = max_scores[curr_room] + score;

                // Bellman-Ford: max_scores converges in N-1 phases if there are no positive cycles
                // rooms that are still updated in the N-th epoch means they are in positive cycles reachable from the start
                if (epoch + 1 == num_rooms) {
                    updated_rooms_in_last_epoch.push_back(adj);
                    continue;
                }
                to_visits.push({epoch + 1, adj});
            }
        }
    }
    if (!updated_rooms_in_last_epoch.empty()) {
        // check whether any of the rooms in positive cycles can also reach the end
        auto to_visits = std::stack<uint>();
        auto visited = std::vector<bool>(num_rooms, false); // optimization: no need to clear after each updated room
        {
            for (auto const &updated_room : updated_rooms_in_last_epoch) {
                to_visits.push(updated_room);
                while (!to_visits.empty()) {
                    auto const curr_room = to_visits.top();
                    to_visits.pop();

                    visited[curr_room] = true;
                    if (curr_room == num_rooms - 1) {
                        std::cout << -1 << '\n';
                        std::exit(0);
                    }

                    for (auto const &[adj, score] : adjss[curr_room]) {
                        if (visited[adj]) continue;
                        to_visits.push({adj});
                    }
                }
            }
        }
    }
    std::cout << max_scores[num_rooms - 1] << '\n';
}