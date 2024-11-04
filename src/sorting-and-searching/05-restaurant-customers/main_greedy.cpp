/*
ideas that won't work:
  - store counters for all a,b
    => a,b <= 1e9 is too large
*/

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_CUSTOMERS;
    {
        std::cin >> NUM_CUSTOMERS;
    }
    auto arrive_ats = std::vector<unsigned>(NUM_CUSTOMERS);
    auto leave_ats = std::vector<unsigned>(NUM_CUSTOMERS);
    {
        for (unsigned i = 0; i < NUM_CUSTOMERS; i++) {
            std::cin >> arrive_ats[i] >> leave_ats[i];
        }
        std::ranges::stable_sort(arrive_ats);
        std::ranges::stable_sort(leave_ats);
    }

    unsigned max_num_customers = 0;
    {
        unsigned leave_at_idx = 0;
        for (auto const &arrive_at : arrive_ats) {
            if (arrive_at < leave_ats[leave_at_idx]) max_num_customers++;
            else leave_at_idx++;
        }
        // ignore unprocessed `leave_at`s because processing them will only decrement `num_customers` and thus will not change `max_num_customers`
    }
    std::cout << max_num_customers << '\n';
}