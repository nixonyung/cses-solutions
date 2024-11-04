// greedy solution: at each step, try to pick the smallest `applicant` and the smallest `appartment`

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_APPLICANTS;
    unsigned NUM_APPARTMENTS;
    unsigned ACCEPTABLE_DIFF;
    {
        std::cin >> NUM_APPLICANTS >> NUM_APPARTMENTS >> ACCEPTABLE_DIFF;
    }
    auto applicants = std::vector<unsigned>(NUM_APPLICANTS);
    auto appartments = std::vector<unsigned>(NUM_APPARTMENTS);
    {
        for (unsigned i = 0; i < NUM_APPLICANTS; i++) {
            std::cin >> applicants[i];
        }
        for (unsigned i = 0; i < NUM_APPARTMENTS; i++) {
            std::cin >> appartments[i];
        }
        std::ranges::stable_sort(applicants);
        std::ranges::stable_sort(appartments);
    }

    unsigned num_matches = 0;
    {
        unsigned applicant_idx = 0;
        unsigned appartment_idx = 0;
        while (applicant_idx < NUM_APPLICANTS && appartment_idx < NUM_APPARTMENTS) {
            auto const &applicant = applicants[applicant_idx];
            auto const &appartment = appartments[appartment_idx];

            // e.q. continue if abs(applicant - appartment) > ACCEPTABLE_DIFF
            if (applicant >= appartment && applicant - appartment > ACCEPTABLE_DIFF) {
                appartment_idx++;
                continue;
            }
            if (appartment >= applicant && appartment - applicant > ACCEPTABLE_DIFF) {
                applicant_idx++;
                continue;
            }

            num_matches++;
            applicant_idx++;
            appartment_idx++;
        }
    }
    std::cout << num_matches << '\n';
}