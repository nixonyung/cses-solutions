#include "utils.hpp"

namespace {
struct Input {
    uint id;
    uint val;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // (ref.) [Stacks - Application - Nearest Smaller Element](https://usaco.guide/gold/stacks?lang=cpp#application---nearest-smaller-element)
    // using a stack because for any `inputs[i]`, inputs before i and >= `inputs[i]` is not a solution for i AND after i

    auto anss = std::vector<uint>(n);
    {
        auto stack = std::vector<Input>();
        stack.reserve(n);

        for (auto i : iota(0U, n)) {
            Input input = {i + 1, read<uint>()};
            while (!stack.empty() && stack.back().val >= input.val) {
                stack.pop_back();
            }
            anss[i] = stack.empty() ? 0 : stack.back().id;
            stack.push_back(input);
        }
    }
    for (auto const &ans : anss) {
        std::cout << ans << ' ';
    }
    std::cout << '\n';
}