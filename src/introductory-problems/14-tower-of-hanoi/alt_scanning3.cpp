// (ref.) [Iterative solution](https://wikiwand.com/en/articles/Tower_of_Hanoi#Iterative_solution)

#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

namespace {
const auto ODD_N_SEQUENCES = std::vector<std::tuple<unsigned, unsigned>>{
    {0, 2},
    {0, 1},
    {1, 2},
};
const auto EVEN_N_SEQUENCES = std::vector<std::tuple<unsigned, unsigned>>{
    {0, 1},
    {0, 2},
    {1, 2},
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }
    unsigned const num_moves = (1U << N) - 1;
    std::cout << num_moves << '\n';

    auto pegs = std::vector<std::stack<unsigned>>(3);
    {
        for (unsigned i = 0; i < N; i++) {
            pegs[0].push(N - 1 - i);
        }
    }
    for (unsigned i = 0; i < num_moves; i++) {
        auto [source, target] = ((N & 1) ? ODD_N_SEQUENCES : EVEN_N_SEQUENCES)[i % 3];
        if (
            !pegs[target].empty()
            && (pegs[source].empty()
                || pegs[source].top() > pegs[target].top())
        ) std::swap(source, target);

        std::cout << source + 1 << ' ' << target + 1 << '\n';

        pegs[target].push(pegs[source].top());
        pegs[source].pop();
    }
}
