// correct implementation but outputs are different from tests

#include <iostream>
#include <map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned TARGET;
    {
        std::cin >> N >> TARGET;
    }
    if (N == 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    auto number_to_id = std::map<unsigned, unsigned>();
    decltype(number_to_id)::key_type number;
    for (unsigned i = 0; i < N; i++) {
        std::cin >> number;

        if (number_to_id.contains(TARGET - number)) {
            std::cout << number_to_id[TARGET - number] + 1 << ' ' << i + 1 << '\n';
            return 0;
        }
        number_to_id[number] = i;
    }
    std::cout << "IMPOSSIBLE\n";
}
