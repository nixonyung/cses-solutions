#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <queue>

// (ref.) [Bipartite graph](https://www.wikiwand.com/en/articles/Bipartite_graph)

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t num_pupils;
    uint32_t num_friendships;
    {
        std::cin >> num_pupils >> num_friendships;
    }

    auto adjss = std::vector<std::vector<uint32_t>>(num_pupils + 1);
    {
        uint32_t pupil1;
        uint32_t pupil2;
        for (uint32_t i = 0; i < num_friendships; i++) {
            std::cin >> pupil1 >> pupil2;
            adjss[pupil1].push_back(pupil2);
            adjss[pupil2].push_back(pupil1);
        }
    }

    auto pupil_to_team = std::vector<uint32_t>(num_pupils + 1, 0);
    {
        auto queue = std::queue<uint32_t>();
        for (uint32_t i = 1; i <= num_pupils; i++) {
            if (pupil_to_team[i] != 0) continue;
            queue.push(i);
            pupil_to_team[i] = 1;

            while (!queue.empty()) {
                auto pupil = queue.front();
                queue.pop();

                for (auto const &adj : adjss[pupil]) {
                    if (pupil_to_team[adj] == pupil_to_team[pupil]) {
                        std::cout << "IMPOSSIBLE\n";
                        std::exit(0);
                    } else if (pupil_to_team[adj] == 0) {
                        queue.push(adj);
                        pupil_to_team[adj] = 3 - pupil_to_team[pupil];
                    }
                }
            }
        }
    }
    for (uint32_t i = 1; i <= num_pupils; i++) {
        std::cout << pupil_to_team[i] << ' ';
    }
    std::cout << '\n';
}