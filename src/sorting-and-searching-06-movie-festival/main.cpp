#include <algorithm>
#include <cstdio>

struct Movie {
    int a;
    int b;
};

int main() {
    int n;
    scanf("%d", &n);

    Movie movies[(int)2e5];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &movies[i].a, &movies[i].b);
    }

    // greedy solution: at each step, try to pick the smallest `b`

    std::sort(movies,
              movies + n,
              [](const auto &lhs, const auto &rhs) {
                  return lhs.b < rhs.b;
              });

    int ans = 0;
    int last_b = 0;
    for (int i = 0; i < n; i++) {
        if (movies[i].a >= last_b) {
            ans++;
            last_b = movies[i].b;
        }
    }
    printf("%d\n", ans);
}