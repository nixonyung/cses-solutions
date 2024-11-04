// (ref.) [Stacks - Application - Nearest Smaller Element](https://usaco.guide/gold/stacks?lang=cpp#application---nearest-smaller-element)
// using a stack because for any `inputs[i]`, inputs before i and >= `inputs[i]` is not a solution for i AND after i

#include <iostream>
#include <stack>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    struct Number {
        unsigned id;
        unsigned val;
    };
    auto s = std::stack<Number>();
    unsigned val;
    for (unsigned i = 0; i < N; i++) {
        std::cin >> val;

        while (!s.empty() && s.top().val >= val) s.pop();
        std::cout << (!s.empty() ? s.top().id + 1 : 0) << ' ';
        s.push({i, val});
    }
    std::cout << '\n';
}