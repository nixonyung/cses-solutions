#include <cstdio>
#include <iterator>
#include <list>

int main() {
    constexpr int K = 2; // choosing every 2 children

    int n;
    scanf("%d", &n);

    // solve by simulation

    // using std::list as it supports O(1) deletion
    std::list<int> childs(n);
    {
        auto it = childs.begin();
        for (int i = 0; i < n; i++, it++) {
            *it = i + 1;
        }
    }

    int child_idx = 0;
    auto it = childs.begin();
    while (!childs.empty()) {
        child_idx += K - 1;
        if (child_idx >= childs.size()) {
            child_idx %= childs.size();
            it = std::next(childs.begin(), child_idx);
        } else {
            std::advance(it, K - 1);
        }

        printf("%d ", *it);
        it = childs.erase(it); // childs.erase invalidates it, and return the new iterator after the erased element
    }
    printf("\n");
}
