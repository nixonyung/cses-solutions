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

// (ref.) [Topological Sorting](https://cp-algorithms.com/graph/topological-sort.html)
// correct implementation but outputs are different from tests
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint num_courses;
    uint num_requirements;
    {
        std::cin >> num_courses >> num_requirements;
    }

    auto prerequisitess = std::vector<std::vector<uint>>(num_courses);
    {
        uint prerequisite;
        uint course;
        for (uint i = 0; i < num_requirements; i++) {
            std::cin >> prerequisite >> course;
            // transform to 0-indexed (personal preference)
            prerequisite--;
            course--;

            prerequisitess[course].push_back(prerequisite);
        }
    }

    auto courses_sorted = std::vector<uint>();
    {
        // "3-colors DFS"
        enum class Color : char {
            NONE,
            IN_PATH,
            HANDLED,
        };
        auto colors = std::vector<Color>(num_courses, Color::NONE);

        auto to_visits = std::stack<uint>();
        for (uint i = 0; i < num_courses; i++) {
            if (colors[i] == Color::HANDLED) continue;

            to_visits.push(i);
            while (!to_visits.empty()) {
                auto const curr = to_visits.top();
                to_visits.pop();

                switch (colors[curr]) {
                case Color::HANDLED:
                    break;
                case Color::NONE: {
                    to_visits.push(curr); // revisit curr AFTER visiting all adjs
                    for (auto const &pre : prerequisitess[curr]) {
                        if (colors[pre] == Color::HANDLED) continue;
                        if (colors[pre] == Color::IN_PATH) {
                            std::cout << "IMPOSSIBLE\n";
                            std::exit(0);
                        }
                        to_visits.push(pre);
                    }
                    colors[curr] = Color::IN_PATH;
                } break;
                case Color::IN_PATH: {
                    courses_sorted.push_back(curr);
                    colors[curr] = Color::HANDLED;
                } break;
                }
            }
        }
    }
    for (auto const &course : courses_sorted) {
        std::cout << course + 1 << ' ';
    }
    std::cout << '\n';
}