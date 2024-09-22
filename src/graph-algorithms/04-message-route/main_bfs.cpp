#include <iostream>
#include <queue>
#include <utility>

namespace {
struct Computer {
    uint id;
    uint path_len = 1;
    uint from = 0;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint num_computers;
    uint num_connections;
    {
        std::cin >> num_computers >> num_connections;
    }

    auto adjss = std::vector<std::vector<uint>>(num_computers + 1);
    {
        uint computer1;
        uint computer2;
        for (int i = 0; std::cmp_less(i, num_connections); i++) {
            std::cin >> computer1 >> computer2;
            adjss[computer1].push_back(computer2);
            adjss[computer2].push_back(computer1);
        }
    }

    {
        auto visited_froms = std::vector<uint>(num_computers + 1, 0);
        auto to_visits = std::queue<Computer>();

        to_visits.push({1});
        while (!to_visits.empty()) {
            auto const [id, path_len, from] = to_visits.front();
            to_visits.pop();

            if (visited_froms[id] != 0) continue;
            visited_froms[id] = from;

            if (id == num_computers) {
                std::cout << path_len << '\n';

                auto path = std::vector<uint>(path_len);
                {
                    uint curr_id = id;
                    for (int i = path_len - 1; i >= 0; i--) {
                        path[i] = curr_id;
                        curr_id = visited_froms[curr_id];
                    }
                }
                for (auto const &computer : path) {
                    std::cout << computer << ' ';
                }
                std::cout << '\n';
                std::exit(0);
            }

            for (auto const &adj : adjss[id]) {
                if (visited_froms[adj] != 0) continue;
                to_visits.push({adj, path_len + 1, id});
            }
        }
    }
    std::cout << "IMPOSSIBLE\n";
}