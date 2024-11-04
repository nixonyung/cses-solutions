#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned TARGET;
    {
        std::cin >> N >> TARGET;
    }

    unsigned num_subarrays = 0;
    {
        auto inputs = std::vector<unsigned>(N);
        unsigned long curr_sum = 0;
        unsigned l = 0;
        for (unsigned r = 0; r < N; r++) {
            std::cin >> inputs[r];

            curr_sum += inputs[r];
            while (curr_sum > TARGET) curr_sum -= inputs[l++];
            if (curr_sum == TARGET) num_subarrays++;
        }
    }
    std::cout << num_subarrays << '\n';
}