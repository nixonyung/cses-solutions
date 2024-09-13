#include "utils.hpp"

namespace {
struct Input {
    uint price;
    uint num_pages;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto budget = read<uint>();
    auto inputs = std::vector<Input>(n);
    {
        for (auto &input : inputs) {
            input.price = read<uint>();
        }
        for (auto &input : inputs) {
            input.num_pages = read<uint>();
        }
    }

    // (ref.) [0-1 knapsack problem](https://www.wikiwand.com/en/articles/Knapsack_problem)

    auto price_to_max_num_pages = std::vector<uint>(budget + 1, 0);
    {
        for (auto const &input : inputs) {
            if (input.price <= budget) {
                for (
                    auto curr_total_price : iota(input.price, budget + 1) |
                                                std::views::reverse // update in reverse order so that `price_to_max_num_pages[curr_total_price - input.price]` will not include the current book
                ) {
                    price_to_max_num_pages[curr_total_price] = std::max(
                        price_to_max_num_pages[curr_total_price],
                        price_to_max_num_pages[curr_total_price - input.price] + input.num_pages
                    );
                }
            }
        }
    }
    std::cout << price_to_max_num_pages[budget] << '\n';
}