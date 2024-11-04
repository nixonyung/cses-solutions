// greedy solution: at each step, try to pick the smallest `movie.end`

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_MOVIES;
    {
        std::cin >> NUM_MOVIES;
    }
    struct Movie {
        unsigned start;
        unsigned end;
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

    unsigned num_movies = 0;
    {
        decltype(Movie::end) old_end = 0;
        for (auto const &[start, end] : movies) {
            if (start < old_end) continue; // note that start == old_end is allowed
            num_movies++;
            old_end = end;
        }
    }
    std::cout << num_movies << '\n';
}