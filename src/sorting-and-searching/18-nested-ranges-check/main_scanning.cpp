#include "utils.hpp"

namespace {
struct Input {
    uint id;
    uint x;
    uint y;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // (ref.) [[Tutorial] Solving Interval Problems with Geometry](https://codeforces.com/blog/entry/98629)
    auto inputs = std::vector<Input>(n);
    {
        for (uint i = 0; auto &input : inputs) {
            input = {i++, read<uint>(), read<uint>()};
        }
    }

    std::ranges::sort(
        inputs,
        [](auto const &lhs, auto const &rhs) {
            return (lhs.x != rhs.x) ? (lhs.x < rhs.x)
                                    : (lhs.y > rhs.y);
        }
    );

    auto anss = std::vector<bool>(n);
    {
        // solving the first line of outputs: check if there is any other ranges [l', r'] a range contains
        // i.e. satisfying l <= l' <= r' <= r
        {
            auto y_min = inputs[n - 1].y;
            anss[inputs[n - 1].id] = false;
            for (auto const &input : inputs | std::views::take(n - 1) | std::views::reverse) {
                anss[input.id] = input.y >= y_min;
                y_min = std::min(y_min, input.y);
            }
        }
        for (auto const &ans : anss) {
            std::cout << (ans ? "1 " : "0 ");
        }
        std::cout << '\n';

        // solving the second line of outputs: check if any other ranges [l', r'] contains the range
        // i.e. satisfying l' <= l <= r <= r'
        {
            auto y_max = inputs[0].y;
            anss[inputs[0].id] = false;
            for (auto const &input : inputs | std::views::drop(1)) {
                anss[input.id] = input.y <= y_max;
                y_max = std::max(y_max, input.y);
            }
            for (auto const &ans : anss) {
                std::cout << (ans ? "1 " : "0 ");
            }
            std::cout << '\n';
        }
    }
}