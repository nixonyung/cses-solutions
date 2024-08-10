#include <cstdio>
#include <unordered_set>

int main() {
    int n;
    scanf("%d", &n);

    /*
    implementations that won't work:
        - store a flag for all x to indicate if it has appeared
            => x <= 1e9 is too large

    We need a data structure to be able to store all n values
    while removing duplicates in O(logn) (good enough for n <= 2e5).
        => use unordered_set
    */
    std::unordered_set<int> s;
    while (n--) {
        int x;
        scanf("%d", &x);
        s.insert(x);
    }
    printf("%ld\n", s.size());
}