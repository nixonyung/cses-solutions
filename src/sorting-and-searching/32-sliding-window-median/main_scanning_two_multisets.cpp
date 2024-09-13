#include "utils.hpp"
#include <set>

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto k = read<uint>();

    // (ref.) [CSES - Sliding Median - Solution 1](https://usaco.guide/problems/cses-1076-sliding-median/solution#solution-1-maintaining-two-multisets)

    {
        auto inputs = std::vector<uint>(n);
        auto lower_set = std::multiset<uint>(); // including the median
        auto upper_set = std::multiset<uint>();
        {
            // handle first k elements first
            // put all elements into set_upper, then move half of them to set_lower
            for (auto i : iota(0U, k)) {
                inputs[i] = read<uint>();
                upper_set.insert(inputs[i]);
            }
            while (upper_set.size() > lower_set.size()) {
                lower_set.insert(lower_set.end(), *upper_set.begin());
                upper_set.erase(upper_set.begin());
            }
            std::cout << *(--lower_set.end()) << ' ';
        }
        {
            for (auto i : iota(k, n)) {
                if (inputs[i - k] <= *(--lower_set.end())) {
                    lower_set.extract(inputs[i - k]);
                } else {
                    upper_set.extract(inputs[i - k]);
                    // want set_upper to have "1 more element" (for odd k) / "the same number of elements" (for even k) than set_lower
                    // this is to make "inserting inputs[i] to set_upper then move to set_lower" always correct
                    upper_set.insert(upper_set.begin(), *(--lower_set.end()));
                    lower_set.erase(--lower_set.end());
                }

                inputs[i] = read<uint>();
                upper_set.insert(inputs[i]);
                while (upper_set.size() > lower_set.size()) {
                    lower_set.insert(lower_set.begin(), *upper_set.begin());
                    upper_set.erase(upper_set.begin());
                }
                std::cout << *(--lower_set.end()) << ' ';
            }
        }
    }
    std::cout << '\n';
}