#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }
    struct Project {
        unsigned start;
        unsigned end; // cannot attend another project on the end day
        unsigned reward;
    };
    auto projects = std::vector<Project>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> projects[i].start >> projects[i].end >> projects[i].reward;
        }
        // sort projects so that prev `max_reward`s must be converged
        std::ranges::stable_sort(
            projects,
            {},
            [](Project const &project) { return project.end; }
        );
    }

    auto max_rewards = std::vector<unsigned long>(N); // max_reward[i] is the max_reward for projects[:i+1]
    {
        for (unsigned i = 0; i < N; i++) {
            // find the largest project.end < projects[i].start
            unsigned const best_attendable_project_idx = (unsigned)std::distance(
                                                             projects.begin(),
                                                             std::ranges::lower_bound(
                                                                 projects | std::views::take(i),
                                                                 projects[i].start,
                                                                 {},
                                                                 [](Project const &project) { return project.end; }
                                                             )
                                                         )
                                                         - 1;
            max_rewards[i] = std::max(
                // do not attend projects[i], then use the best result from previous projects
                (i != 0) ? max_rewards[i - 1] : 0,
                // attend projects[i], then use the best result from previous projects that ends before projects[i] starts
                projects[i].reward + ((best_attendable_project_idx < i) ? max_rewards[best_attendable_project_idx] : 0)
            );
        }
    }
    std::cout << max_rewards[N - 1] << '\n';
}