#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    /*
    ans = the number of "10" (= 2*5) as a factor in [1,N]
    As there must be more "5" than "2" in [1,N], we can just count the number of "5".

    Note that we have to count all "5" in a number.
    e.g. 25 (= 5*5) has two "5".

    ans = (number of "5") + (number of "25") + (number of "625") + ...
        = n/5 + n/25 + n/625 + ...
    */
    unsigned long num_trailing_zeros = 0;
    {
        N /= 5;
        for (; N > 0; N /= 5) num_trailing_zeros += N;
    }
    std::cout << num_trailing_zeros << '\n';
}