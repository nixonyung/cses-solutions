#include "utils.hpp"

namespace {
static inline std::tuple<uint, uint, uint, uint> cut_rectangle(
    uint side_to_cut,
    uint cut,
    uint side_to_keep
) {
    uint rectangle1_side1 = cut;
    uint rectangle2_side1 = side_to_cut - cut;
    uint rectangle1_side2 = side_to_keep;
    uint rectangle2_side2 = side_to_keep;
    // optimization: reducing search space
    if (rectangle1_side1 > rectangle1_side2) {
        std::swap(rectangle1_side1, rectangle1_side2);
    }
    if (rectangle2_side1 > rectangle2_side2) {
        std::swap(rectangle2_side1, rectangle2_side2);
    }
    return {
        rectangle1_side1,
        rectangle1_side2,
        rectangle2_side1,
        rectangle2_side2
    };
}
} // namespace

int main() {
    enable_fast_io();

    auto target_width = read<uint>();
    auto target_height = read<uint>();
    // optimization: reducing search space
    if (target_width > target_height) {
        std::swap(target_width, target_height);
    }

    // (ref.) [CSES DP section editorial - Edit Distance](https://codeforces.com/blog/entry/70018#:~:text=Edit%20Distance)

    auto min_num_cutss = std::vector<uint>((target_width + 1) * (target_height + 1), std::numeric_limits<uint>::max());
    {
        // initial state
        {
            // min_num_cuts for 1 x N square/rectrangles = N-1
            for (auto curr_height : iota(1U, target_height + 1)) {
                min_num_cutss[1 * (target_height + 1) + curr_height] = curr_height - 1;
            }
        }
        // recurrence
        for (auto curr_width : iota(2U, target_width + 1)) {
            // no cuts needed for squares
            min_num_cutss[curr_width * (target_height + 1) + curr_width] = 0;

            for (auto curr_height : iota(curr_width + 1, target_height + 1)) {
                for (
                    auto const &[side_to_cut, side_to_keep] : {
                        std::make_tuple(curr_width, curr_height), // cut by width, i.e. cut vertically
                        std::make_tuple(curr_height, curr_width)  // cut by height, i.e. cut horizontally
                    }
                ) {
                    for (auto cut : iota(1U, side_to_cut)) {
                        auto [width1, height1, width2, height2] = cut_rectangle(side_to_cut, cut, side_to_keep);
                        min_num_cutss[curr_width * (target_height + 1) + curr_height] = std::min(
                            min_num_cutss[curr_width * (target_height + 1) + curr_height],
                            1 + (min_num_cutss[width1 * (target_height + 1) + height1] +
                                 min_num_cutss[width2 * (target_height + 1) + height2])
                        );
                    }
                }
            }
        }
    }
    std::cout << min_num_cutss[target_width * (target_height + 1) + target_height] << '\n';
}