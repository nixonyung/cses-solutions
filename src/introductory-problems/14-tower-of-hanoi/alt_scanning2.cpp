// alternative implementation of main_scanning
// (ref.) [Inorder Tree Traversal without Recursion](https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/)

#include <iostream>
#include <stack>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }
    std::cout << (1U << N) - 1 << '\n';

    {
        enum Peg {
            LEFT,
            MIDDLE,
            RIGHT,
        };
        struct State {
            unsigned num_disks;
            Peg source;
            Peg spare;
            Peg target;
        };
        auto s = std::stack<State>();
        State curr = {N, Peg::LEFT, Peg::MIDDLE, Peg::RIGHT};
        while (curr.num_disks > 0 || !s.empty()) {
            while (curr.num_disks > 0) {
                s.push(curr);
                // move to "left child", i.e. move_disks(num_disks-1, source, target, spare)
                curr = {
                    .num_disks = curr.num_disks - 1,
                    .source = curr.source,
                    .spare = curr.target,
                    .target = curr.spare
                };
            }
            // pop and print the leftmost node
            curr = s.top();
            s.pop();
            std::cout << curr.source + 1 << ' ' << curr.target + 1 << '\n';
            // move to "right child", i.e. move_disks(num_disks-1, spare, source, target)
            curr = {
                .num_disks = curr.num_disks - 1,
                .source = curr.spare,
                .spare = curr.source,
                .target = curr.target
            };
        }
    }
}
