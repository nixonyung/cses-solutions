#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);
    /*
    observe the pattern:
        when n=1, there are 1 odd numbers in [1,n] -> sum is odd and thus NOT POSSIBLE
        when n=2, there are 1 -> sum is odd and thus NOT POSSIBLE
        when n=3, there are 2
        when n=4, there are 2
        when n=5, there are 3 -> sum is odd and thus NOT POSSIBLE
        when n=6, there are 3 -> sum is odd and thus NOT POSSIBLE
        when n=7, there are 4
        when n=8, there are 4
        ...

        notice that we can early-fail for n=1,2,5,6,...
    */
    if (!((n - 1) & 2)) {
        printf("NO\n");
        return 0;
    }

    /*
    following the test outputs:
        when n=7 (n is odd):
            group1 = [7,4,3]
            group2 = [6,5,2,1]
        when n=8 (n is even):
            group1 = [8,5,4,1]
            group2 = [7,6,3,2]
        ...

        notice that the numbers (from n down-to 1) are put in groups 1,2,2,1,1,2,2,1,...
    */
    printf("YES\n");
    printf("%d\n", n >> 1);
    for (int i = 0; i < n; i++) {
        if ((i & 3) == 0 || (i & 3) == 3) {
            printf("%d ", n - i);
        }
    }
    printf("\n%d\n", (n + 1) >> 1);
    for (int i = 0; i < n; i++) {
        if ((i & 3) == 1 || (i & 3) == 2) {
            printf("%d ", n - i);
        }
    }
    printf("\n");
}