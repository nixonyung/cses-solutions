#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    unsigned long num_subarrays = 0;
    {
        auto numbers = std::vector<int>(N);
        long numbers_sum = 0;
        auto prefix_mod_counter = std::vector<unsigned>(N);
        {
            prefix_mod_counter[0] = 1;
        }
        for (unsigned i = 0; i < N; i++) {
            std::cin >> numbers[i];
            // (ref.) [Fastest way to get a positive modulo in C/C++](https://stackoverflow.com/questions/14997165/fastest-way-to-get-a-positive-modulo-in-c-c)
            numbers_sum = ((numbers_sum + numbers[i]) % N + N) % N;
            num_subarrays += prefix_mod_counter[numbers_sum]++; // want curr_mod_sum - prefix_mod_sum = 0
        }
    }
    std::cout << num_subarrays << '\n';
}