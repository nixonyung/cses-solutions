#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }
    auto number_to_pos = std::vector<unsigned>(N + 1);
    {
        decltype(number_to_pos)::value_type number;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> number;
            number_to_pos[number] = i;
        }
    }

    // `num_rounds` is the number of increasing subsequence in `pos`s
    unsigned num_rounds = 1;
    {
        for (unsigned i = 2; i <= N; i++) {
            if (number_to_pos[i] < number_to_pos[i - 1]) num_rounds++;
        }
    }
    std::cout << num_rounds << '\n';
}