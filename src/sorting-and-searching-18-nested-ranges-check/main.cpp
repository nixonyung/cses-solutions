#include <algorithm>
#include <cstdio>

struct Input {
    int x;
    int y;
    int index;
};

int main() {
    constexpr int MAX_N = (int)2e5;

    int n;
    std::scanf("%d", &n);

    // (ref.) [[Tutorial] Solving Interval Problems with Geometry](https://codeforces.com/blog/entry/98629)

    Input inputs[MAX_N];
    for (int i = 0; i < n; i++) {
        std::scanf("%d %d", &inputs[i].x, &inputs[i].y);
        inputs[i].index = i;
    }

    std::sort(inputs,
              inputs + n,
              [](const auto &lhs, const auto &rhs) {
                  return (lhs.x != rhs.x) ? (lhs.x < rhs.x)
                                          : (lhs.y > rhs.y);
              });

    // solving the first line of outputs: check if there is any other ranges [l', r'] a range contains
    // i.e. satisfying l <= l' <= r' <= r
    bool anss[MAX_N];
    {
        int y_min = inputs[n - 1].y;
        anss[inputs[n - 1].index] = false;
        for (int i = n - 2; i >= 0; i--) {
            anss[inputs[i].index] = inputs[i].y >= y_min;
            y_min = std::min(y_min, inputs[i].y);
        }
    }
    for (int i = 0; i < n; i++) {
        std::printf(anss[i] ? "1 " : "0 ");
    }
    std::printf("\n");

    // solving the second line of outputs: check if any other ranges [l', r'] contains the range
    // i.e. satisfying l' <= l <= r <= r'
    {
        int y_max = inputs[0].y;
        anss[inputs[0].index] = false;
        for (int i = 1; i < n; i++) {
            anss[inputs[i].index] = inputs[i].y <= y_max;
            y_max = std::max(y_max, inputs[i].y);
        }
    }
    for (int i = 0; i < n; i++) {
        std::printf(anss[i] ? "1 " : "0 ");
    }
    std::printf("\n");
}