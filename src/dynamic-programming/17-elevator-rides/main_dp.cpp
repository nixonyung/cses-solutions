#include "utils.hpp"

namespace {
struct State {
    uint num_rides;
    uint last_ride_sum_weights;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto allowed_weight = read<uint>();
    auto weights = std::vector<uint>(n);
    {
        std::ranges::generate(weights, read<uint>);
    }

    // (ref.) [Elevator Rides](https://codeforces.com/blog/entry/105092#:~:text=Elevator%20Rides%20(1653))

    auto states = std::vector<State>(1U << n, {std::numeric_limits<uint>::max(), std::numeric_limits<uint>::max()}); // bitmask DP
    {
        // initial state
        for (auto const &i : iota(0U, n)) {
            states[1U << i] = {1, weights[i]};
        }

        // recurrence
        for (auto const &num_ones : iota(2U, n + 1)) {
            uint bitmask = (1U << num_ones) - 1; // bitmask with `num_ones` trailing ones
            // TODO: this loop can be parallelized (as any state with `num_ones` ones only depends on with `num_ones-1` ones) but how?
            do {
                // for each `weight_idx`, iterate states without `weight_idx`
                // bitmask DP is used because the weights in the iterated states does not need to have index < `weight_idx`,
                // i.e. e.g. the optimal solution may be obtained by adding the 3rd weight to (2nd, 5th, 6th)
                for (auto const &weight_idx : iota(0U, n)) {
                    if (bitmask & (1 << weight_idx)) {
                        auto const &[num_rides, last_ride_sum_weights] = states[bitmask ^ (1 << weight_idx)];
                        states[bitmask] = std::min(
                            states[bitmask],
                            (last_ride_sum_weights + weights[weight_idx] <= allowed_weight)
                                ? State{num_rides, last_ride_sum_weights + weights[weight_idx]}
                                : State{num_rides + 1, weights[weight_idx]},
                            BINARY_FN(lhs, rhs) {
                                return (lhs.num_rides != rhs.num_rides) ? (lhs.num_rides < rhs.num_rides)
                                                                        : (lhs.last_ride_sum_weights < rhs.last_ride_sum_weights);
                            }
                        );
                    }
                }
            } while ((bitmask = next_bits_permutation(bitmask)) < (1U << n));
        }
    }
    std::cout << states[(1U << n) - 1].num_rides << '\n';
}