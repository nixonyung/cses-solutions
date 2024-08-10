#include <cstdio>
#include <set>

int main() {
    int n;
    scanf("%d", &n);

    // greedy solution: put k to the smallest tower larger than k
    std::multiset<int> tower_tops;
    while (n--) {
        int k;
        scanf("%d", &k);

        auto it = tower_tops.upper_bound(k);
        if (it != tower_tops.end()) {
            tower_tops.erase(it);
        }
        tower_tops.insert(k);
    }
    printf("%ld\n", tower_tops.size());
}