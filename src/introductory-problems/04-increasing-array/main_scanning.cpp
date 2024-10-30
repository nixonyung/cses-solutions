#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    unsigned long min_num_moves = 0;
    {
        unsigned number;
        decltype(number) max_number = 0;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> number;
            max_number = std::max(max_number, number);
            min_num_moves += max_number - number;
        }
    }
    std::cout << min_num_moves << '\n';
}