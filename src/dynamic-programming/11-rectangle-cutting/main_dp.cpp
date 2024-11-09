// (ref.) [CSES DP section editorial - Rectangle Cutting](https://codeforces.com/blog/entry/70018#:~:text=Rectangle%20Cutting)

#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned WIDTH;
    unsigned HEIGHT;
    {
        std::cin >> WIDTH >> HEIGHT;
        // optimization: reducing search space
        if (WIDTH > HEIGHT) std::swap(WIDTH, HEIGHT);
    }

    auto cut_rectangle = [](
                             unsigned side_to_cut,
                             unsigned cut,
                             unsigned side_to_keep
                         ) {
        unsigned rectangle1_side1 = cut;
        unsigned rectangle1_side2 = side_to_keep;
        unsigned rectangle2_side1 = side_to_cut - cut;
        unsigned rectangle2_side2 = side_to_keep;
        // optimization: reducing search space
        if (rectangle1_side1 > rectangle1_side2) std::swap(rectangle1_side1, rectangle1_side2);
        if (rectangle2_side1 > rectangle2_side2) std::swap(rectangle2_side1, rectangle2_side2);
        return std::make_tuple(
            rectangle1_side1,
            rectangle1_side2,
            rectangle2_side1,
            rectangle2_side2
        );
    };
    auto min_num_cutss = std::vector<unsigned>((WIDTH + 1) * (HEIGHT + 1), -1U);
    {
        for (unsigned width = 1; width <= WIDTH; width++) {
            // optimization: only fill min_num_cutss where width <= height
            for (unsigned height = width; height <= HEIGHT; height++) {
                // min_num_cuts for 1 x N square/rectrangles = N-1
                if (width == 1) {
                    min_num_cutss[width * (HEIGHT + 1) + height] = height - 1;
                    continue;
                }
                // no cuts needed for squares
                if (height == width) {
                    min_num_cutss[width * (HEIGHT + 1) + height] = 0;
                    continue;
                }
                for (
                    auto const &[side_to_cut, side_to_keep] : {
                        std::make_tuple(width, height), // cut by width, i.e. cut vertically
                        std::make_tuple(height, width)  // cut by height, i.e. cut horizontally
                    }
                ) {
                    for (unsigned cut = 1; cut < side_to_cut; cut++) {
                        auto const [width1, height1, width2, height2] = cut_rectangle(side_to_cut, cut, side_to_keep);
                        min_num_cutss[width * (HEIGHT + 1) + height] = std::min(
                            min_num_cutss[width * (HEIGHT + 1) + height],
                            1 + min_num_cutss[width1 * (HEIGHT + 1) + height1] + min_num_cutss[width2 * (HEIGHT + 1) + height2]
                        );
                    }
                }
            }
        }
    }
    std::cout << min_num_cutss[WIDTH * (HEIGHT + 1) + HEIGHT] << '\n';
}