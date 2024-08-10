#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    // hard-coded solutions for n <= 3
    if (n == 1) {
        printf("1\n");
        return 0;
    }
    if (n == 2 || n == 3) {
        printf("NO SOLUTION\n");
        return 0;
    }

    // solution: enumerate even numbers increasingly, then enumerate odd numbers increasingly
    for (int i = 2; i <= n; i += 2) {
        printf("%d ", i);
    }
    for (int i = 1; i <= n; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
}