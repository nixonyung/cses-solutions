#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    auto min_num_stepss = std::vector<unsigned>(N + 1, -1U);
    {
        min_num_stepss[0] = 0;

        for (unsigned i = 1; i <= N; i++) {
            for (unsigned _i = i; _i > 0; _i /= 10) {
                auto const digit = _i % 10;
                if (min_num_stepss[i - digit] == -1U) continue;
                min_num_stepss[i] = std::min(min_num_stepss[i], 1 + min_num_stepss[i - digit]);
            }
        }
    }
    std::cout << min_num_stepss[N] << '\n';
}