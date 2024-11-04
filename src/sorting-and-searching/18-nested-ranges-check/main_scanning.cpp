// (ref.) [[Tutorial] Solving Interval Problems with Geometry](https://codeforces.com/blog/entry/98629)

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    struct Range {
        unsigned id;
        unsigned x;
        unsigned y;
    };
    auto ranges = std::vector<Range>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> ranges[i].x >> ranges[i].y;
            ranges[i].id = i;
        }
        std::ranges::sort(
            ranges,
            [](Range const &lhs, Range const &rhs) {
                return (lhs.x != rhs.x) ? (lhs.x < rhs.x)
                                        : (lhs.y > rhs.y);
            }
        );
    }

    auto anss = std::vector<bool>(N); // reuse memory for the two questions
    {
        // solving the first question:
        // check if there is any other ranges [l', r'] a range [l, r] contains, i.e. satisfying l <= l' <= r' <= r
        {
            auto min_y = ranges[N - 1].y;
            anss[ranges[N - 1].id] = false;
            for (unsigned i = N - 2; i <= N - 2; i--) {
                anss[ranges[i].id] = ranges[i].y >= min_y;
                min_y = std::min(min_y, ranges[i].y);
            }
        }
        for (auto const &ans : anss) {
            std::cout << (ans ? "1 " : "0 ");
        }
        std::cout << '\n';

        // solving the second question:
        // check if any other ranges [l', r'] contains the range [l, r], i.e. satisfying l' <= l <= r <= r'
        {
            auto max_y = ranges[0].y;
            anss[ranges[0].id] = false;
            for (unsigned i = 1; i < N; i++) {
                anss[ranges[i].id] = ranges[i].y <= max_y;
                max_y = std::max(max_y, ranges[i].y);
            }
        }
        for (auto const &ans : anss) {
            std::cout << (ans ? "1 " : "0 ");
        }
        std::cout << '\n';
    }
}