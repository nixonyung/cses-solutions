// TODO: [Algorithm to return all combinations of k elements from n](https://stackoverflow.com/questions/127704/algorithm-to-return-all-combinations-of-k-elements-from-n)

#include <algorithm>
#include <cstdio>

// naive implementation is good enough given n <= 8
int factorial(int x) {
    int ans = 1;
    while (x--) {
        ans *= x + 1;
    }
    return ans;
}

int main() {
    int count[26];
    for (int i = 0; i < 26; i++) {
        count[i] = 0;
    }

    char s[9];
    int s_len;
    scanf("%s%n", s, &s_len);
    for (int i = 0; i < s_len; i++) {
        count[s[i] - 'a']++;
    }

    // (ref.) [Multinomial theorem - Interpretations](https://omni.wikiwand.com/en/articles/Multinomial_theorem#Interpretations)
    int num_total = factorial(s_len);
    for (int i = 0; i < 26; i++) {
        num_total /= factorial(count[i]);
    }
    printf("%d\n", num_total);

    // (ref.) [how can print only unique Permutations of a string?](https://stackoverflow.com/questions/67679226/how-can-print-only-unique-permutations-of-a-string)
    std::sort(s, s + s_len);
    do {
        printf("%s\n", s);
    } while (std::next_permutation(s, s + s_len));
}
