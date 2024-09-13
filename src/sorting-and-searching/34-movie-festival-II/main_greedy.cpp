#include "utils.hpp"
#include <set>

namespace {
struct Input {
    uint start;
    uint end; // exclusive
};
} // namespace

int main() {
    enable_fast_io();

    auto num_movies = read<uint>();
    auto num_members = read<uint>();

    // (ref.) [CSES - Movie Festival II](https://usaco.guide/problems/cses-1632-movie-festival-ii/solution)

    auto inputs = std::vector<Input>(num_movies);
    {
        for (auto &input : inputs) {
            input = {read<uint>(), read<uint>()};
        }
        radix_sort(
            inputs,
            [](auto const &input) {
                return input.end;
            }
        );
    }

    uint max_num_watched_movies = 0;
    {
        auto member_available_froms = std::multiset<uint>();
        for (auto const &input : inputs) {
            // find largest member_available_from <= input.start
            auto it = member_available_froms.lower_bound(input.start + 1);
            if (it != member_available_froms.begin()) {
                it--;
                member_available_froms.insert(member_available_froms.end(), input.end);
                member_available_froms.erase(it);
                max_num_watched_movies++;
            } else if (member_available_froms.size() < num_members) {
                member_available_froms.insert(member_available_froms.end(), input.end);
                max_num_watched_movies++;
            }
        }
    }
    std::cout << max_num_watched_movies << '\n';
}