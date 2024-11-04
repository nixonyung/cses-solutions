// (ref.) [CSES Solutions - Subarray Distinct Values](https://www.geeksforgeeks.org/cses-solutions-subarray-distinct-values/)

#include <iostream>
#include <map>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned TARGET;
    {
        std::cin >> N >> TARGET;
    }

    unsigned long num_subarrays = 0;
    {
        auto numbers = std::vector<unsigned>(N);
        auto counter = std::map<decltype(numbers)::value_type, unsigned>();
        unsigned num_unique = 0;
        unsigned l = 0;
        for (unsigned r = 0; r < N; r++) {
            std::cin >> numbers[r];

            if (counter[numbers[r]] == 0) num_unique++;
            counter[numbers[r]]++;
            while (num_unique > TARGET) {
                counter[numbers[l]]--;
                if (counter[numbers[l]] == 0) num_unique--;
                l++;
            }
            num_subarrays += r - l + 1; // any arrays in inputs[subarray_start : (i+1)] will satisfy having AT MOST k distinct values,
                                        // only count suffix arrays to avoid double counting
        }
    }
    std::cout << num_subarrays << '\n';
}