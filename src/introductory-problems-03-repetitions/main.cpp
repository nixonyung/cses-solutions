#include <algorithm>
#include <cstdio>

int main() {
    char s[(int)1e6 + 1];
    int s_len;
    scanf("%s%n", s, &s_len);

    int ans = 1;
    char curr_ch = s[0];
    int curr_len = 1;
    for (int i = 1; i < s_len; i++) {
        if (s[i] == curr_ch) {
            curr_len++;
        } else {
            // lazily evaluate ans only when curr_ch changes
            ans = std::max(ans, curr_len);

            curr_ch = s[i];
            curr_len = 1;
        }
    }
    ans = std::max(ans, curr_len);
    printf("%d\n", ans);
}