#define VERSION_DIRECT_COMPUTATION 1
#define VERSION_INCREMENTAL 2

#define VERSION VERSION_INCREMENTAL

#if VERSION == VERSION_DIRECT_COMPUTATION
#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    // (ref.) [Gray code](https://cp-algorithms.com/algebra/gray-code.html)
    for (int i = 0; i < (1 << n); i++) {
        int code = i ^ (i >> 1);

        for (int j = n - 1; j >= 0; j--) {
            printf((code & (1 << j)) ? "1" : "0");
        }
        printf("\n");
    }
}
#elif VERSION == VERSION_INCREMENTAL
#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    // (ref.) [Constructing an n-bit Gray code](https://omni.wikiwand.com/en/articles/Gray_code#Constructing_an_n-bit_Gray_code)
    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Introductory%20Problems/Gray%20Code.cpp>
    int code = 0;
    for (int i = 0; i < (1 << n); i++) {
        code ^= (i == 0) ? 0 : (1 << __builtin_ctz(i));

        for (int j = n - 1; j >= 0; j--) {
            printf((code & (1 << j)) ? "1" : "0");
        }
        printf("\n");
    }
}
#endif
