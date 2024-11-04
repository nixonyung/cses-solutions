#include <iostream>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    auto unique_numbers = std::set<unsigned>();
    {
        decltype(unique_numbers)::value_type number;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> number;
            unique_numbers.insert(number);
        }
    }
    std::cout << unique_numbers.size() << '\n';
}