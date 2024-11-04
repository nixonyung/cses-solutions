#include <iostream>
#include <list>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    auto childs = std::list<unsigned>(N); // using std::list as it supports O(1) deletion
    {
        decltype(childs)::value_type i = 0;
        for (auto &child : childs) {
            child = i++;
        }
    }
    for (auto it = childs.begin(); !childs.empty(); it = childs.erase(it)) {
        if (it == childs.end()) it = childs.begin();
        it++;
        if (it == childs.end()) it = childs.begin();
        std::cout << *it + 1 << ' ';
    }
    std::cout << '\n';
}
