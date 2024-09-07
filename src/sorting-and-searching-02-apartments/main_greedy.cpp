#include "utils.hpp"

int main() {
    enable_fast_io();

    auto num_applicants = read<uint>();
    auto num_appartments = read<uint>();
    auto k = read<uint>();

    auto applicants = std::vector<uint>(num_applicants);
    auto appartments = std::vector<uint>(num_appartments);
    {
        for (auto &applicants : applicants) {
            applicants = read<uint>();
        }
        for (auto &appartments : appartments) {
            appartments = read<uint>();
        }
    }

    // greedy solution: at each step, try to pick the smallest `a` and the smallest `b`

    radix_sort(applicants);
    radix_sort(appartments);

    uint ans = 0;
    {
        uint applicant_idx = 0;
        uint appartments_idx = 0;
        while (applicant_idx < num_applicants && appartments_idx < num_appartments) {
            if (applicants[applicant_idx] + k < appartments[appartments_idx]) {
                applicant_idx++;
            } else if (appartments[appartments_idx] + k < applicants[applicant_idx]) {
                appartments_idx++;
            } else {
                ans++;
                applicant_idx++;
                appartments_idx++;
            }
        }
    }
    std::cout << ans << '\n';
}