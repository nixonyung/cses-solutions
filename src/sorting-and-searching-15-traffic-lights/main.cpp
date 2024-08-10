#define VERSION_REAL_TIME 1
#define VERSION_OFFLINE 2

#define VERSION VERSION_OFFLINE

#if VERSION == VERSION_REAL_TIME
#include <cstdio>
#include <iterator>
#include <set>

int main() {
    int x, n;
    scanf("%d %d", &x, &n);

    // (ref.) [CSES - Traffic Lights - Solution 1](https://usaco.guide/problems/cses-1163-traffic-lights/solution#solution-1)
    std::set<int> poss = {0, x}; // init with dummy values to handle out-of-bound
    std::multiset<int> lengths = {x};
    for (int i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);

        auto it = poss.insert(p).first;
        auto next = std::next(it);
        auto prev = std::prev(it);
        lengths.erase(lengths.find(*next - *prev));
        lengths.insert(*next - *it);
        lengths.insert(*it - *prev);
        printf("%d ", *std::prev(lengths.end()));
    }
    printf("\n");
}
#elif VERSION == VERSION_OFFLINE
#include <cstdio>
#include <iterator>
#include <set>

int main() {
    int x, n;
    scanf("%d %d", &x, &n);

    // (ref.) [CSES - Traffic Lights - Solution 2](https://usaco.guide/problems/cses-1163-traffic-lights/solution#solution-2---going-backwards)

    int poss[(int)2e5];
    for (int i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);
        poss[i] = p;
    }
    std::set<int> poss_sorted(poss, poss + n);
    // dummy values to handle out-of-bound
    poss_sorted.insert(0);
    poss_sorted.insert(x);

    int anss[(int)2e5];
    anss[n - 1] = 0;
    int prev_pos = *poss_sorted.begin();
    for (auto it = std::next(poss_sorted.begin()); it != poss_sorted.end(); it++) {
        int pos = *it;
        anss[n - 1] = std::max(anss[n - 1], pos - prev_pos);
        prev_pos = pos;
    }

    for (int i = n - 1; i > 0; i--) {
        auto it = poss_sorted.find(poss[i]);
        anss[i - 1] = std::max(anss[i], *std::next(it) - *std::prev(it));
        poss_sorted.erase(it);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", anss[i]);
    }
    printf("\n");
}
#endif