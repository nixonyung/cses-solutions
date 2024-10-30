// (ref.) [Recursive solution](https://wikiwand.com/en/articles/Tower_of_Hanoi#Recursive_solution)

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }
    /*
    consider the recursive solution, observe that:
        hanoi(1) = 1
        hanoi(2) = 1+2*hanoi(1) = 1+2     = 3
        hanoi(3) = 1+2*hanoi(2) = 1+2+4   = 7
        hanoi(4) = 1+2*hanoi(3) = 1+2+4+8 = 15
        ...
    we have hanoi(n) = 1+2*hanoi(n-1)+1 = sum_{k=1}^{n-1} 2^k = 2^n - 1
    */
    std::cout << (1U << N) - 1 << '\n';

    {
        enum Peg {
            LEFT,
            MIDDLE,
            RIGHT,
        };
        auto move_disks = [](
                              unsigned n,
                              Peg source,
                              Peg spare,
                              Peg target
                          ) {
            auto impl = [](
                            auto impl_ref,
                            unsigned n,
                            Peg source,
                            Peg spare,
                            Peg target
                        ) -> void {
                if (n != 1) impl_ref(impl_ref, n - 1, source, target, spare);
                std::cout << source + 1 << ' ' << target + 1 << '\n';
                if (n != 1) impl_ref(impl_ref, n - 1, spare, source, target);
            };
            impl(impl, n, source, spare, target);
        };
        move_disks(N, Peg::LEFT, Peg::MIDDLE, Peg::RIGHT);
    }
}
