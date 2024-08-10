#include <cstdio>
#include <set>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    /*
    given that each customer need to get a ticket at "real-time",
    we need a data structure to sort the values and support O(logn) deletion (good enough for n <= 2e5).
        => use multiset ("set" but allow duplicates)
    */
    std::multiset<int> hs;
    while (n--) {
        int h;
        scanf("%d", &h);
        hs.insert(h);
    }

    while (m--) {
        int t;
        scanf("%d", &t);

        if (hs.empty()) {
            printf("-1\n");
            continue;
        }
        // (ref.) [Find largest element smaller than current with STL](https://stackoverflow.com/a/55087805)
        auto it = hs.upper_bound(t);
        if (it != hs.begin()) {
            it--;
            printf("%d\n", *it);
            hs.erase(it);
        } else {
            printf("-1\n");
        }
    }
}