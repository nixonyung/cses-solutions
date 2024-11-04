// (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Nearest%20Smaller%20Values.cpp>

#include <climits>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    auto numbers = std::vector<unsigned>(N);
    auto nearest_smaller_poss = std::vector<unsigned>(N, UINT_MAX);
    for (unsigned i = 0; i < N; i++) {
        std::cin >> numbers[i];

        auto &pos = nearest_smaller_poss[i];
        {
            pos = i - 1;
            while (pos != UINT_MAX && numbers[pos] >= numbers[i]) pos = nearest_smaller_poss[pos];
        }
        std::cout << pos + 1 << ' ';
    }
    std::cout << '\n';
}