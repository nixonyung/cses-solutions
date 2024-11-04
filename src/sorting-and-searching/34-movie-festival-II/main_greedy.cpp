// (ref.) [CSES - Movie Festival II](https://usaco.guide/problems/cses-1632-movie-festival-ii/solution)

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_MOVIES;
    unsigned NUM_MEMBERS;
    {
        std::cin >> NUM_MOVIES >> NUM_MEMBERS;
    }

    struct Movie {
        unsigned start;
        unsigned end; // `movie.end == prev_movie.start` is allowed
    };
    auto movies = std::vector<Movie>(NUM_MOVIES);
    {
        for (unsigned i = 0; i < NUM_MOVIES; i++) {
            std::cin >> movies[i].start >> movies[i].end;
        }
        std::ranges::stable_sort(
            movies,
            {},
            [](Movie const &movie) { return movie.end; }
        );
    }

    unsigned max_num_watched_movies = 0;
    {
        auto member_available_froms = std::multiset<unsigned>();
        {
            for (unsigned i = 0; i < NUM_MEMBERS; i++) {
                member_available_froms.insert(0);
            }
        }
        for (auto const &[start, end] : movies) {
            // find largest member_available_from <= input.start
            auto it = member_available_froms.lower_bound(start + 1);
            if (it == member_available_froms.begin()) continue;
            max_num_watched_movies++;
            member_available_froms.extract(--it);
            member_available_froms.insert(member_available_froms.end(), end);
        }
    }
    std::cout << max_num_watched_movies << '\n';
}