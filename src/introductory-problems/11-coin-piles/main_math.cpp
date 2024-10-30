#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_TESTS;
    {
        std::cin >> NUM_TESTS;
    }

    unsigned a;
    unsigned b;
    while (NUM_TESTS--) {
        std::cin >> a >> b;

        // as each move always remove 3 coins, it is not possible to remove the remainer if the total number of coins is not a multiple of 3
        if ((a + b) % 3) {
            std::cout << "NO\n";
            continue;
        }
        if ((a > b * 2) || (b > a * 2)) {
            std::cout << "NO\n";
            continue;
        }
        /*
        Otherwise a solution always exist:
          if a > b:
            find k s.t. a-3k = 2(b-3k), i.e. k = (2b-a)/3
            then the solution is to choose k*(1,2) and k*(2,1), then (b-3k)*(2,1)
          else:
            find k s.t. b-3k = 2(a-3k), i.e. k = (2a-b)/3
            then the solution is to choose k*(1,2) and k*(2,1), then (a-3k)*(1,2)
        */
        std::cout << "YES\n";
    }
}