#include "../../lib/cses_io.hpp"
#include <algorithm>

struct Movie {
    int a;
    int b;

    friend std::istream &operator>>(std::istream &in, Movie &movie) {
        return in >> movie.a >> movie.b;
    }
};

int main() {
    cses::enable_fast_io();

    auto n = cses::read<int>();
    auto movies = cses::read_vector<Movie>(n);

    // greedy solution: at each step, try to pick the smallest `b`

    std::ranges::sort(movies, [](auto const &lhs, auto const &rhs) { return lhs.b < rhs.b; });

    auto ans = 0;
    {
        auto last_b = 0;
        for (auto i = 0; i < n; i++) {
            if (movies[i].a >= last_b) {
                ans++;
                last_b = movies[i].b;
            }
        }
    }
    std::cout << ans << '\n';
}