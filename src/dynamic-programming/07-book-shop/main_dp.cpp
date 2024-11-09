// (ref.) [0-1 knapsack problem](https://www.wikiwand.com/en/articles/Knapsack_problem)

#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned BUDGET;
    {
        std::cin >> N >> BUDGET;
    }
    struct Book {
        unsigned price;
        unsigned num_pages;
    };
    auto books = std::vector<Book>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> books[i].price;
        }
        for (unsigned i = 0; i < N; i++) {
            std::cin >> books[i].num_pages;
        }
    }

    auto budget_to_max_num_pages = std::vector<unsigned>(BUDGET + 1, 0);
    {
        for (auto const &[price, num_pages] : books) {
            for (unsigned budget = BUDGET; budget >= price; budget--) {
                budget_to_max_num_pages[budget] = std::max(
                    budget_to_max_num_pages[budget],
                    budget_to_max_num_pages[budget - price] + num_pages
                );
            }
        }
    }
    std::cout << budget_to_max_num_pages[BUDGET] << '\n';
}