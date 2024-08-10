#define VERSION_BINARY_SEARCH 1
#define VERSION_POINTERS 2

#define VERSION VERSION_POINTERS

#include <algorithm>
#include <cstdio>

struct Input {
    int a;
    int index;
};

int main() {
    int n, x;
    scanf("%d %d", &n, &x);
    if (n == 1) {
        printf("IMPOSSIBLE\n");
        return 0;
    }

    Input inputs[(int)2e5];
    for (int i = 0; i < n; i++) {
        scanf("%d", &inputs[i].a);
        inputs[i].index = i;
    }

    // using `stable_sort` just to make the output matches with the test output,
    // using `sort` is also correct and should be faster
    std::stable_sort(inputs,
                     inputs + n,
                     [](const auto &lhs, const auto &rhs) {
                         return lhs.a < rhs.a;
                     });

    /*
    analyzing VERSION_BINARY_SEARCH:
        Time complexity = O(log(n) + log(n-1) + ... + log(1))  (because of running binary search on array with decreasing size)
                        = O(nlogn)

        Should be faster when there are a lot of elements to skip at each increment of `left`,
        e.g.
            x = 100
            a[] = [1, 11, 50, 50, ...(hundreds of 90), ...(hundreds of 100)]
                          ^   ^

    analyzing VERSION_POINTERS:
        Time complexity = O(n) because left and right together will at most traverse all `a` once.
        It is also more cache-friendly.

        Should be faster when there are only a few elements to skip at each increment of `left`,
        e.g.
            x = 100
            a[] = [...(hundreds of 1), ...(hundreds of 11), 50, 50, 90, 100]
                                                            ^   ^
    */
#if VERSION == VERSION_BINARY_SEARCH
    for (int left = 0; left < n - 1; left++) {
        // using `upper_bound` just to make the output matches with the test output,
        // using `lower_bound` should also work
        int right = (int)(std::upper_bound(inputs + left,
                                           inputs + n,
                                           x - inputs[left].a,
                                           [](const auto &val, const auto &input) {
                                               return val < input.a;
                                           }) -
                          inputs);
        /*
        pointers are not valid if either:
            - left == right-1 (because the resulting indices have to be distinct)
            - left > right-1 (logically wrong)
        */
        if (left < right - 1 && inputs[left].a + inputs[right - 1].a == x) {
            printf("%d %d\n", inputs[left].index + 1, inputs[right - 1].index + 1);
            return 0;
        }
    }
    printf("IMPOSSIBLE\n");
#elif VERSION == VERSION_POINTERS
    // right is the smallest index s.t. a[left] + a[right] > x
    int right = n;
    for (int left = 0; left < right - 1; left++) {
        if (inputs[left].a + inputs[right - 1].a == x) {
            printf("%d %d\n", inputs[left].index + 1, inputs[right - 1].index + 1);
            return 0;
        }

        // decrement `right` while maintaining a[left] + a[right] > x
        while (left < right - 1 && inputs[left].a + inputs[right - 1].a > x) {
            right--;
        }
        if (left < right - 1 && inputs[left].a + inputs[right - 1].a == x) {
            printf("%d %d\n", inputs[left].index + 1, inputs[right - 1].index + 1);
            return 0;
        }
    }
    printf("IMPOSSIBLE\n");
#endif
}
