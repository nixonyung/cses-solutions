#include <algorithm>
#include <climits>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    long max_subarray_sum = LONG_MIN;
    {
        decltype(max_subarray_sum) subarray_sum = 0;
        int number;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> number;
            subarray_sum += number;
            max_subarray_sum = std::max(max_subarray_sum, subarray_sum);
            /*
            if subarray_sum > 0:
                keep subarray_sum, as it may constitute to a larger subarray sum
            else:
                reset subarray_sum to 0, as a negative subarray_sum will only make subsequent sum smaller
            */
            subarray_sum = std::max(subarray_sum, 0L);
        }
    }
    std::cout << max_subarray_sum << '\n';
}