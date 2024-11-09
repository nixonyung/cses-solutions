// (ref.) [Elevator Rides](https://codeforces.com/blog/entry/105092#:~:text=Elevator%20Rides%20(1653))

#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned WEIGHT_UPPER_BOUND;
    {
        std::cin >> N >> WEIGHT_UPPER_BOUND;
    }
    auto weights = std::vector<unsigned>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> weights[i];
        }
    }

    struct State {
        unsigned num_rides;
        unsigned last_ride_weights_sum;
    };
    // bitmask DP is used because the weights in the iterated states does not need to have index < `weight_idx`,
    // e.g. the optimal solution may be obtained by adding the 3rd weight to (2nd, 5th, 6th) or adding the 2nd to (3rd, 5th, 6th) or ...
    auto states = std::vector<State>(1U << N, {-1U, -1U}); // bitmask DP
    {
        // iterate bitmasks in increasing order so that states[i ^ (1 << weight_idx)] must be converged (for having fewer set bits and thus smaller than `i`)
        for (unsigned i = 1; i < (1U << N); i++) {
            for (unsigned weight_idx = 0; weight_idx < N; weight_idx++) {
                if (!(i & (1 << weight_idx))) continue;

                auto const &[num_rides, last_ride_weights_sum] = states[i ^ (1 << weight_idx)];
                states[i] = ((i ^ (1 << weight_idx)) != 0)
                                ? std::min(
                                      states[i],
                                      (last_ride_weights_sum + weights[weight_idx] <= WEIGHT_UPPER_BOUND)
                                          // can add weights[weight_idx] to "last_ride"
                                          ? State{num_rides, last_ride_weights_sum + weights[weight_idx]}
                                          // cannot add weights[weight_idx] to "last_ride", so need a new ride
                                          : State{num_rides + 1, weights[weight_idx]},
                                      [](State const &lhs, State const &rhs) {
                                          return (lhs.num_rides != rhs.num_rides) ? (lhs.num_rides < rhs.num_rides)
                                                                                  : (lhs.last_ride_weights_sum < rhs.last_ride_weights_sum);
                                      }
                                  )
                                : State{1, weights[weight_idx]};
            }
        }
    }
    std::cout << states[(1U << N) - 1].num_rides << '\n';
}