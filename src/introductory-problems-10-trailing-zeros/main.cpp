#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = int();
    std::cin >> n;

    /*
    ans = the number of "10" (= 2*5) as a factor in [1,N]
    As there must be more "5" than "2" in [1,N], we can just count the number of "5".

    Note that we have to count all "5" in a number.
    e.g. 25 (= 5*5) has two "5".

    ans = (number of "5") + (number of "25") + (number of "625") + ...
        = n/5 + n/25 + n/625 + ...
    */
    auto ans = 0;
    auto temp = n;
    while (temp > 0) {
        temp /= 5;
        ans += temp;
    }
    std::cout << ans << '\n';
}