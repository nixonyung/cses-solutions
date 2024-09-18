#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // (ref.) [Longest increasing subsequence](https://www.wikiwand.com/en/articles/Longest_increasing_subsequence#Efficient_algorithms)

    auto length_to_min_ending_number = std::vector<uint>();
    {
        length_to_min_ending_number.reserve(n);
        for (auto _ : iota(0U, n)) {
            uint number = read<uint>();

            // find the length of the longest subsequence `number` can form
            // by finding the largest "ending number" < number
            auto it = std::ranges::lower_bound(length_to_min_ending_number, number);
            if (it == length_to_min_ending_number.end()) {
                // number > any "ending number" -> can append number to curr longest subsequence
                length_to_min_ending_number.push_back(number);
            } else {
                // number can append to the subsequence ending with number *(it-1),
                // so *it = min(*it, number)
                //
                // optimization: we know *it >= number because of `lower_bound`
                *it = number;
            }
        }
    }
    std::cout << length_to_min_ending_number.size() << '\n';
}