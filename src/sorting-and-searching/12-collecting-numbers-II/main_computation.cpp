#include "utils.hpp"

namespace {
inline uint delta(
    int pos1,
    int pos2,
    std::vector<int> &inputs,
    std::vector<int> &poss
) {
    if (inputs[pos1] + 1 == inputs[pos2]) {
        return (poss[inputs[pos1] - 1] > pos1) +
               (pos1 > pos2) +
               (pos2 > poss[inputs[pos2] + 1]);
    } else if (inputs[pos2] + 1 == inputs[pos1]) {
        return (poss[inputs[pos2] - 1] > pos2) +
               (pos2 > pos1) +
               (pos1 > poss[inputs[pos1] + 1]);
    } else {
        return (poss[inputs[pos1] - 1] > pos1) +
               (pos1 > poss[inputs[pos1] + 1]) +
               (poss[inputs[pos2] - 1] > pos2) +
               (pos2 > poss[inputs[pos2] + 1]);
    }
}
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto num_tests = read<uint>();

    auto inputs = std::vector<int>(n);   // inputs[1] is the first (i.e. pos=1) input
    auto poss = std::vector<int>(n + 2); // poss[x] is the position of x (so the first input x has poss[x] = 1)
    /*
    side properties:
        - inputs[poss[x]] = x
        - poss[inputs[i]] = i
    */
    {
        // dummy values to handle index-out-of-bound
        poss[0] = 0;
        poss[n + 1] = n + 1;
        for (auto i : iota(1U, n + 1)) {
            auto input = read<uint>();
            inputs[i] = input;
            poss[input] = i;
        }
    }

    // ans is the number of increasing subsequence in `pos`
    auto ans = 1;
    for (auto i : iota(1U, n)) {
        if (poss[i] > poss[i + 1]) {
            ans++;
        }
    }

    while (num_tests--) {
        auto pos1 = read<uint>();
        auto pos2 = read<uint>();

        ans -= delta(pos1, pos2, inputs, poss);
        std::swap(poss[inputs[pos1]], poss[inputs[pos2]]);
        std::swap(inputs[pos1], inputs[pos2]);
        ans += delta(pos1, pos2, inputs, poss);

        std::cout << ans << '\n';
    }
}