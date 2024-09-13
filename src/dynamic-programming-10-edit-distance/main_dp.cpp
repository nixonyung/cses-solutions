#include "utils.hpp"

int main() {
    enable_fast_io();

    auto source = read<string>();
    auto target = read<string>();

    // (ref.) [Levenshtein distance](https://www.wikiwand.com/en/articles/Levenshtein_distance)

    auto edit_distances = std::vector<uint>(target.size() + 1); // storing edit distances for the last source_len is enough
    {
        // initial state: source = empty string
        {
            for (auto target_len : iota(0U, target.size() + 1)) {
                // optimal solution is to add all characters from target to source
                edit_distances[target_len] = target_len;
            }
        }

        // recurrence
        auto next_edit_distances = std::vector<uint>(target.size() + 1); // preallocate memory
        for (auto source_len : iota(1U, source.size() + 1)) {
            // when target = empty string,
            // optimal solution is to remove all characters from source
            next_edit_distances[0] = source_len;

            for (auto target_len : iota(1U, target.size() + 1)) {
                if (source[source_len - 1] == target[target_len - 1]) {
                    // greedily skip the current characters if they are the same
                    next_edit_distances[target_len] = edit_distances[target_len - 1];
                } else {
                    next_edit_distances[target_len] =
                        1 +
                        std::min(
                            {
                                // removing one character from source
                                edit_distances[target_len],
                                // adding one character to source, e.q. removing one character from target
                                next_edit_distances[target_len - 1],
                                // replacing one character in source, e.q. removing one character from both source and target
                                edit_distances[target_len - 1],
                            }
                        );
                }
            }
            std::swap(edit_distances, next_edit_distances);
        }
    }
    std::cout << edit_distances.back() << '\n';
}