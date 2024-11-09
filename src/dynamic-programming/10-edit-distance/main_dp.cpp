// (ref.) [Levenshtein distance](https://www.wikiwand.com/en/articles/Levenshtein_distance)

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string SOURCE;
    std::string TARGET;
    {
        std::cin >> SOURCE >> TARGET;
    }

    auto edit_distances = std::vector<unsigned>(TARGET.size() + 1); // optimization: only store edit distances for one iteration of `source_len`
    {
        auto new_edit_distances = edit_distances;
        for (unsigned source_len = 0; source_len <= SOURCE.size(); source_len++) {
            for (unsigned target_len = 0; target_len <= TARGET.size(); target_len++) {
                new_edit_distances[target_len] =
                    // when `source` is an empty string, the optimal solution is to add all characters from `target` to `source`
                    (source_len == 0) ? target_len
                    // when `target` is an empty string, the optimal solution is to remove all characters from `source`
                    : (target_len == 0) ? source_len
                    // when `source` and `target` ends with the same character, skip the character, e.q. removing one character from both `source` and `target` WITHOUT any cost
                    : (SOURCE[source_len - 1] == TARGET[target_len - 1]) ? edit_distances[target_len - 1]
                                                                         // otherwise the recurrence relation is:
                                                                         : 1 + std::ranges::min({
                                                                               // removing one character from `source`
                                                                               edit_distances[target_len],
                                                                               // adding one character to `source`, e.q. removing one character from `target`
                                                                               new_edit_distances[target_len - 1],
                                                                               // replacing one character in `source`, e.q. removing one character from both `source` and `target`
                                                                               edit_distances[target_len - 1],
                                                                           });
            }
            std::swap(edit_distances, new_edit_distances);
        }
    }
    std::cout << edit_distances[TARGET.size()] << '\n';
}