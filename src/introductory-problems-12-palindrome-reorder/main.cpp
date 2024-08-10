#include <cstdio>

int main() {
    int count[26];
    for (int i = 0; i < 26; i++) {
        count[i] = 0;
    }

    char s[(int)1e6 + 1];
    int s_len;
    scanf("%s%n", s, &s_len);
    for (int i = 0; i < s_len; i++) {
        count[s[i] - 'A']++;
    }

    int odd_idx = -1;
    for (int i = 0; i < 26; i++) {
        if (count[i] & 1) {
            // at most 1 character can appear odd number of times
            if (odd_idx != -1) {
                printf("NO SOLUTION\n");
                return 0;
            }
            odd_idx = i;
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < count[i] / 2; j++) {
            printf("%c", 'A' + i);
        }
    }
    // move the odd part to the center
    // following the tests: move only a single character to the center
    if (odd_idx != -1) {
        printf("%c", 'A' + odd_idx);
    }
    for (int i = 25; i >= 0; i--) {
        for (int j = 0; j < count[i] / 2; j++) {
            printf("%c", 'A' + i);
        }
    }
    printf("\n");
}