#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    unsigned min_num_steps = 0;
    {
        while (N > 0) {
            unsigned max_digit = 0;
            {
                unsigned _N = N;
                while (_N > 0) {
                    max_digit = std::max(max_digit, _N % 10);
                    _N /= 10;
                }
            }
            N -= max_digit;
            min_num_steps++;
        }
    }
    std::cout << min_num_steps << '\n';
}