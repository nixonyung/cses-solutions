// (ref.) [CSES - Sliding Cost](https://usaco.guide/problems/cses-1077-sliding-cost/solution)

#include <iostream>
#include <set>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned K;
    {
        std::cin >> N >> K;
    }

    auto numbers = std::vector<unsigned>(N);
    auto numbers_lower = std::multiset<decltype(numbers)::value_type>(); // including the median
    auto numbers_upper = std::multiset<decltype(numbers)::value_type>();
    unsigned long lower_sum = 0;
    unsigned long upper_sum = 0;
    {
        for (unsigned i = 0; i < K; i++) {
            std::cin >> numbers[i];
            upper_sum += numbers[i];
            numbers_upper.insert(numbers[i]);
        }
        while (numbers_lower.size() < numbers_upper.size()) {
            lower_sum += *numbers_upper.begin();
            upper_sum -= *numbers_upper.begin();
            numbers_lower.insert(numbers_lower.end(), *numbers_upper.begin());
            numbers_upper.extract(numbers_upper.begin());
        }
    }

    /*
    total cost = sum{abs(input_i - median)}
               = (upper_sum - median * k/2) + (median * (k+1)/2 - lower_sum)
               = {
                  upper_sum - lower_sum + median (if k is odd)
                  upper_sum - lower_sum          (if k is even)
                 }
    */
    std::cout << upper_sum - lower_sum + (K & 1) * *numbers_lower.rbegin() << ' ';
    {
        for (unsigned i = K; i < N; i++) {
            std::cin >> numbers[i];

            if (numbers[i - K] <= *numbers_lower.rbegin()) {
                numbers_lower.extract(numbers[i - K]);
                numbers_upper.insert(numbers[i]);
                lower_sum -= numbers[i - K];
                upper_sum += numbers[i];
                lower_sum += *numbers_upper.begin();
                upper_sum -= *numbers_upper.begin();
                numbers_lower.insert(numbers_lower.begin(), *numbers_upper.begin());
                numbers_upper.extract(numbers_upper.begin());
            } else {
                numbers_upper.extract(numbers[i - K]);
                numbers_lower.insert(numbers[i]);
                upper_sum -= numbers[i - K];
                lower_sum += numbers[i];
                upper_sum += *numbers_lower.rbegin();
                lower_sum -= *numbers_lower.rbegin();
                numbers_upper.insert(numbers_upper.begin(), *numbers_lower.rbegin());
                numbers_lower.extract(--numbers_lower.end());
            }
            std::cout << upper_sum - lower_sum + (K & 1) * *numbers_lower.rbegin() << ' ';
        }
    }
    std::cout << '\n';
}