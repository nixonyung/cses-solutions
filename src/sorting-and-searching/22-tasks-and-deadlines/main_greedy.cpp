/*
(ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Tasks%20and%20Deadlines.cpp>

reward = \sum{deadline_i - finish_time_i}
       = \sum{deadline_i} - \sum{finish_time_i}

Note that deadlines are constants.
Then we can simply get the maximum reward by minimizing the finishing times.
This is done by always choosing the task with the shortest duration.
*/

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    struct Task {
        unsigned duration;
        unsigned deadline;
    };
    auto tasks = std::vector<Task>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> tasks[i].duration >> tasks[i].deadline;
        }
        std::ranges::stable_sort(
            tasks,
            {},
            [](Task const &task) { return task.duration; }
        );
    }

    long rewards_sum = 0;
    {
        unsigned long t = 0;
        for (auto const &[duration, deadline] : tasks) {
            t += duration;
            rewards_sum += (long)deadline - t;
        }
    }
    std::cout << rewards_sum << '\n';
}