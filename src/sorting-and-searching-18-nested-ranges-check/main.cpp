#include "../../lib/cses_io.hpp"
#include <algorithm>

struct Input {
    int x;
    int y;

    friend std::istream &operator>>(std::istream &in, Input &input) {
        return in >> input.x >> input.y;
    }
};

int main() {
    cses::enable_fast_io();

    auto n = cses::read<int>();

    // (ref.) [[Tutorial] Solving Interval Problems with Geometry](https://codeforces.com/blog/entry/98629)
    auto inputs = cses::read_vector_with_ids<Input>(n);

    std::ranges::sort(
        inputs,
        [](auto const &lhs, auto const &rhs) {
            return (lhs.val.x != rhs.val.x) ? (lhs.val.x < rhs.val.x)
                                            : (lhs.val.y > rhs.val.y);
        }
    );

    // solving the first line of outputs: check if there is any other ranges [l', r'] a range contains
    // i.e. satisfying l <= l' <= r' <= r
    auto anss = std::vector<bool>(n);
    {
        auto y_min = inputs[n - 1].val.y;
        anss[inputs[n - 1].id] = false;
        for (auto i = n - 2; i >= 0; i--) {
            anss[inputs[i].id] = inputs[i].val.y >= y_min;
            y_min = std::min(y_min, inputs[i].val.y);
        }
    }
    for (auto i = 0; i < n; i++) {
        std::cout << (anss[i] ? "1 " : "0 ");
    }
    std::cout << '\n';

    // solving the second line of outputs: check if any other ranges [l', r'] contains the range
    // i.e. satisfying l' <= l <= r <= r'
    {
        auto y_max = inputs[0].val.y;
        anss[inputs[0].id] = false;
        for (auto i = 1; i < n; i++) {
            anss[inputs[i].id] = inputs[i].val.y <= y_max;
            y_max = std::max(y_max, inputs[i].val.y);
        }
    }
    for (auto i = 0; i < n; i++) {
        std::cout << (anss[i] ? "1 " : "0 ");
    }
    std::cout << '\n';
}