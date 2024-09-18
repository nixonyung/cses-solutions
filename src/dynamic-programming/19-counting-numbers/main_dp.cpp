#include "utils.hpp"

namespace {
bool check(long prefix) {
    auto [quo, rem] = std::ldiv(prefix, 10);
    uint prev_digit = (uint)rem;
    prefix = quo;
    while (prefix > 0) {
        auto [quo, digit] = std::ldiv(prefix, 10);
        if (digit == prev_digit) {
            return false;
        }
        prev_digit = (uint)digit;
        prefix = quo;
    }
    return true;
}

// count num_no_adjacent_digits in [0,bound)
ulong count(ulong bound) {
    // (ref.) [CSES DP section Editorial - Counting Numbers](https://codeforces.net/blog/entry/105092#:~:text=Counting%20Numbers%20(2220))

    ulong num_no_adjacent_digits = 0;
    /*
    Note that while having multiple zeroes in the middle / multiple trailing zeroes are invalid,
    having multiple "leading" zeroes is valid.
    - e.g. 10012 is invalid, but 0012 (i.e. 12) is valid

    The DP array has to,treat multiple leading zeroes as invalid so that future states can reuse the array,
    so we need to have extra variable(s) to count the numbers having multiple leading zeroes.
    */
    ulong num_no_adjacent_digits_with_multiple_leading_zeros = 0;
    {
        auto digit_counter = std::vector<ulong>(10, 1);
        ulong sum_digit_counter = 10; // optimization

        /*
        Perform DP digit-by-digit.

        e.g.  [0,102234) can be divided to subranges:
            [102230,102233] (fix 5 digits, append [0,4))
                  ^      ^
            [102200,102229] (fix 4 digits, append [00,30))
                 ^      ^
            [102000,102199] (fix 3 digits, append [000,200))
                ^      ^
            [100000,101999] (fix 2 digits, append [0000,2000))
               ^      ^
            [100000,109999] (fix 1 digits, append [00000,00000)) --> IGNORED
              ^      ^
            [000000,099999] (no fixed digits, append [000000,100000))
             ^      ^
        */
        auto [prefix, digit] = std::ldiv(bound, 10);
        {
            auto next_digit_counter = std::vector<ulong>(10); // preallocate memory
            ulong next_sum_digit_counter = 0;                 // preallocate memory

            // while there is fixed prefix
            while (prefix > 0) {
                num_no_adjacent_digits_with_multiple_leading_zeros += digit_counter[0];

                if (check(prefix)) {
                    for (auto const &i : iota(0, digit)) {
                        if (i != prefix % 10) {
                            num_no_adjacent_digits += digit_counter[i];
                        }
                    }
                }

                // TODO: optimization: digit_counter[i] at the k-th iteration is simply 9^k, but why?
                next_sum_digit_counter = 0;
                for (auto const &i : iota(0U, 10U)) {
                    next_digit_counter[i] = sum_digit_counter - digit_counter[i];
                    next_sum_digit_counter += next_digit_counter[i];
                }
                std::swap(digit_counter, next_digit_counter);
                sum_digit_counter = next_sum_digit_counter;

                auto [quo, rem] = std::ldiv(prefix, 10);
                prefix = quo;
                digit = rem;
            }
        }
        {
            // no fixed prefix
            for (auto const &i : iota(0, digit)) {
                num_no_adjacent_digits += digit_counter[i];
            }
        }
    }
    return num_no_adjacent_digits + num_no_adjacent_digits_with_multiple_leading_zeros;
}
} // namespace

int main() {
    enable_fast_io();

    auto a = read<ulong>();
    auto b = read<ulong>();

    std::cout << count(b + 1) - count(a) << '\n';
}