#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    unsigned num_rounds = 0;
    {
        auto appeareds = std::vector<bool>(N, false);

        unsigned number;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> number;
            appeareds[number] = true;
            if (number == 0 || !appeareds[number - 1]) num_rounds++;
        }
    }
    std::cout << num_rounds << '\n';
}