// (ref.) [CSES DP section Editorial - Counting Numbers](https://codeforces.net/blog/entry/105092#:~:text=Counting%20Numbers%20(2220))

#include <iostream>

namespace {
const unsigned BASE = 10;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned long LOWER_BOUND;
    unsigned long UPPER_BOUND;
    {
        std::cin >> LOWER_BOUND >> UPPER_BOUND;
        UPPER_BOUND++; // transform to right-open interval
    }

    auto count = [](unsigned long upper_bound) -> unsigned long {
        /*
        Count the number of numbers in [0, upper_bound) where no two adjacent digits are the same.
        e.g. consider upper_bound=340123 (i.e. range [0,340123)), the range can be divided to the following subranges:

            [340120,340123): 5-digit prefix "34012", 1-digit choices [0,2]
                  ^      ^
            [340100,340120): 4-digit prefix "1022",  2-digit choices [00,19]
                 ^^     ^^
            [340000,340100): 3-digit prefix "102",   3-digit choices [000,099]
                ^^^    ^^^
            [340000,340000): 2-digit prefix "10",    4-digit choices [0000,x999] --> INVALID RANGE
               ^^^^   ^^^^
            [300000,340000): 1-digit prefix "1",     5-digit choices [00000,39999]
              ^^^^^  ^^^^^
            [100000,300000): no prefix,              6-digit choices [100000,299999]
             ^^^^^^ ^^^^^^
            [ 10000,100000): no prefix,              5-digit choices [10000,99999]
              ^^^^^  ^^^^^
            [  1000, 10000): no prefix,              4-digit choices [1000,9999]
               ^^^^   ^^^^
            [   100,  1000): no prefix,              3-digit choices [100,999]
                ^^^    ^^^
            [    10,   100): no prefix,              2-digit choices [10,99]
                 ^^     ^^
            [     1,    10): no prefix,              1-digit choices [1,9]
                  ^      ^
            [     0,     1): no prefix,              single choice [0,0]
        */

        if (upper_bound == 0) return 0;

        unsigned long ans = 0;
        unsigned num_digits = 0;
        {
            unsigned digit = (unsigned)(upper_bound % BASE);
            decltype(digit) prev_digit; // 1 sig. fig. before `digit`
            unsigned long num_choices = 1;
            while (upper_bound > 0) {
                upper_bound /= BASE;
                num_digits++;
                prev_digit = (unsigned)(upper_bound % BASE);

                // invalidate previous `ans` if found same adjacent digits
                if (digit == prev_digit) ans = 0;
                // ignore "INVALID RANGE"
                if (digit != 0) {
                    // choose `num_digits` integers where
                    // the first integer is in [0, digit) and not the same as prev_digit, and
                    // subsequent integers are not the same as the one before
                    ans += (digit - (prev_digit < digit)) * num_choices;
                }
                digit = prev_digit;
                num_choices *= BASE - 1;
            }
        }
        // (this step can be computed in the loop above, but decided not to for readability purposes)
        {
            unsigned long num_choices = BASE - 1;
            for (unsigned i = 1; i < num_digits; i++) {
                // choose `num_digits` integers where
                // the first integer is in [1, BASE) and
                // subsequent digits are not the same as the one before
                ans += num_choices;
                num_choices *= BASE - 1;
            }
        }
        return ans + 1; // add the "single choice" 0
    };
    std::cout << count(UPPER_BOUND) - count(LOWER_BOUND) << '\n';
}