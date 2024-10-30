#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    /*
    observe the pattern:
        when n=1, there are 1 odd numbers in [1,n] -> sum is odd so NOT POSSIBLE
        when n=2, there are 1 odd numbers -> sum is odd so NOT POSSIBLE
        when n=3, there are 2 odd numbers
        when n=4, there are 2 odd numbers
        when n=5, there are 3 odd numbers -> sum is odd so NOT POSSIBLE
        when n=6, there are 3 odd numbers -> sum is odd so NOT POSSIBLE
        when n=7, there are 4 odd numbers
        when n=8, there are 4 odd numbers
        ...

        notice that we can early-fail for n=1,2,5,6,...
    */
    if ((N & 3) == 1 || (N & 3) == 2) {
        std::cout << "NO\n";
        return 0;
    }

    /*
    following the test outputs:
        when n=7 (n is odd):
            group1 = [7,4,3]
            group2 = [6,5,2,1]
        when n=8 (n is even):
            group1 = [8,5,4,1]
            group2 = [7,6,3,2]
        ...

        notice that the numbers (from n down-to 1) are put in groups 1,2,2,1,1,2,2,1,...
    */
    std::cout << "YES\n"
              << (N >> 1) << '\n';
    for (unsigned i = 0; i < N; i++) {
        if ((i & 3) == 0 || (i & 3) == 3) {
            std::cout << N - i << ' ';
        }
    }
    std::cout << '\n'
              << ((N + 1) >> 1) << '\n';
    for (unsigned i = 0; i < N; i++) {
        if ((i & 3) == 1 || (i & 3) == 2) {
            std::cout << N - i << ' ';
        }
    }
    std::cout << '\n';
}