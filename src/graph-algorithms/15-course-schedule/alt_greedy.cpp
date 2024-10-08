#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>

// custom primitive data types
typedef unsigned int uint;
typedef unsigned long ulong;
typedef std::size_t usize;
typedef std::make_signed_t<std::size_t> isize;

// (ref.) [Kahn's algorithm for Topological Sorting](https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/)
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint num_courses;
    uint num_requirements;
    {
        std::cin >> num_courses >> num_requirements;
    }

    auto num_prerequisitess = std::vector<uint>(num_courses, 0);
    auto required_byss = std::vector<std::vector<uint>>(num_courses);
    {
        uint prerequisite;
        uint course;
        for (uint i = 0; i < num_requirements; i++) {
            std::cin >> prerequisite >> course;
            // transform to 0-indexed (personal preference)
            prerequisite--;
            course--;

            num_prerequisitess[course]++;
            required_byss[prerequisite].push_back(course);
        }
    }

    auto courses_sorted = std::vector<uint>(num_courses);
    {
        auto to_visits = std::queue<uint>();
        for (uint i = 0; i < num_courses; i++) {
            if (num_prerequisitess[i] == 0) to_visits.push(i);
        }

        uint num_courses_sorted = 0;
        while (!to_visits.empty()) {
            auto const curr = to_visits.front();
            to_visits.pop();
            courses_sorted[num_courses_sorted++] = curr + 1;

            for (auto const &adj : required_byss[curr]) {
                num_prerequisitess[adj]--;
                if (num_prerequisitess[adj] == 0) to_visits.push(adj);
            }
        }
        if (num_courses_sorted != num_courses) {
            std::cout << "IMPOSSIBLE\n";
            std::exit(0);
        }
    }
    for (auto const &course : courses_sorted) {
        std::cout << course << ' ';
    }
    std::cout << '\n';
}