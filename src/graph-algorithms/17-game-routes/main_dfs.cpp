#include <climits>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

// custom primitive data types
typedef unsigned int uint;
typedef unsigned long ulong;
typedef std::size_t usize;
typedef std::make_signed_t<std::size_t> isize;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const ulong MOD = 1e9 + 7;

    uint num_levels;
    uint num_teleporters;
    {
        std::cin >> num_levels >> num_teleporters;
    }

    auto adjss = std::vector<std::vector<uint>>(num_levels);
    {
        uint start;
        uint end;
        for (uint i = 0; i < num_teleporters; i++) {
            std::cin >> start >> end;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            adjss[start].push_back(end);
        }
    }

    auto num_ways = std::vector<ulong>(num_levels, 0);
    {
        num_ways[num_levels - 1] = 1;

        // "3-colors DFS"
        enum class Color : char {
            NONE,
            IN_PATH,
            HANDLED,
        };
        auto colors = std::vector<Color>(num_levels, Color::NONE);

        auto to_visits = std::stack<uint>();
        to_visits.push(0);
        while (!to_visits.empty()) {
            auto const curr = to_visits.top();
            to_visits.pop();

            switch (colors[curr]) {
            case Color::HANDLED:
                break;
            case Color::NONE: {
                to_visits.push(curr); // revisit curr AFTER visiting all adjs
                for (auto const &adj : adjss[curr]) {
                    if (colors[adj] != Color::NONE) continue;
                    to_visits.push(adj);
                }
                colors[curr] = Color::IN_PATH;
            } break;
            case Color::IN_PATH: {
                for (auto const &adj : adjss[curr]) {
                    num_ways[curr] += num_ways[adj];
                }
                num_ways[curr] %= MOD;
                colors[curr] = Color::HANDLED;
            } break;
            }
        }
    }
    std::cout << num_ways[0] << '\n';
}