// greedy solution: at each step, try to pair the smallest and the largest `weight`

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_CHILDS;
    unsigned ALLOWED_WEIGHT;
    {
        std::cin >> NUM_CHILDS >> ALLOWED_WEIGHT;
    }
    auto weights = std::vector<unsigned>(NUM_CHILDS);
    {
        for (unsigned i = 0; i < NUM_CHILDS; i++) {
            std::cin >> weights[i];
        }
        std::ranges::stable_sort(weights);
    }

    unsigned num_matches = 0;
    {
        unsigned l = 0;
        unsigned r = NUM_CHILDS - 1;
        while (r < NUM_CHILDS && l <= r) {
            num_matches++;
            if (weights[l] + weights[r] <= ALLOWED_WEIGHT) l++;
            r--;
        }
    }
    std::cout << num_matches << '\n';
}