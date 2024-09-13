#include "utils.hpp"
#include <set>

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto k = read<uint>();

    // (ref.) [CSES - Sliding Cost](https://usaco.guide/problems/cses-1077-sliding-cost/solution)

    {
        auto inputs = std::vector<uint>(n);
        auto lower_set = std::multiset<uint>(); // including the median
        ulong lower_sum = 0;
        auto upper_set = std::multiset<uint>();
        ulong upper_sum = 0;
        {
            for (auto i : iota(0U, k)) {
                inputs[i] = read<uint>();
                upper_set.insert(inputs[i]);
            }
            while (upper_set.size() > lower_set.size()) {
                lower_set.insert(lower_set.end(), *upper_set.begin());
                upper_set.erase(upper_set.begin());
            }

            for (auto const &input : lower_set) {
                lower_sum += input;
            }
            for (auto const &input : upper_set) {
                upper_sum += input;
            }

            // total cost = sum{abs(input_i - median)} = (upper_sum - median * k/2) + (median * (k+1)/2 - lower_sum)
            std::cout << (long)upper_sum - (long)lower_sum + ((k & 1) * (long)*(--lower_set.end())) << ' ';
        }
        {
            for (auto i : iota(k, n)) {
                if (inputs[i - k] <= *(--lower_set.end())) {
                    lower_sum -= inputs[i - k];
                    lower_set.extract(inputs[i - k]);
                } else {
                    upper_sum -= inputs[i - k];
                    upper_set.extract(inputs[i - k]);
                    upper_sum += *(--lower_set.end());
                    upper_set.insert(upper_set.begin(), *(--lower_set.end()));
                    lower_sum -= *(--lower_set.end());
                    lower_set.erase(--lower_set.end());
                }

                inputs[i] = read<uint>();
                upper_sum += inputs[i];
                upper_set.insert(inputs[i]);
                while (upper_set.size() > lower_set.size()) {
                    lower_sum += *upper_set.begin();
                    lower_set.insert(lower_set.begin(), *upper_set.begin());
                    upper_sum -= *upper_set.begin();
                    upper_set.erase(upper_set.begin());
                }
                std::cout << (long)upper_sum - (long)lower_sum + ((k & 1) * (long)*(--lower_set.end())) << ' ';
            }
        }
    }
    std::cout << '\n';
}