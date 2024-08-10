#include <cstdio>
#include <cstdlib>

int main() {
    int q;
    scanf("%d", &q);

    while (q--) {
        long k;
        scanf("%ld", &k);

        /*
        given k, try to find num and digit_idx (digit_idx=0 means MSB)
            e.g. for k=7 (the string is 1234567):              num=7,  digit_idx=0
            e.g. for k=19 (the string is 1234567891011121314): num=14, digit_idx=1

        consider the case where the number of digits is fixed to 3 by zero-padding (and using small k):
            e.g. for k=19 (the string is now 0010020030040050060):    num=7, digit_idx=0
            e.g. for k=20 (the string is now 00100200300400500600):   num=7, digit_idx=1
            e.g. for k=21 (the string is now 001002003004005006007):  num=7, digit_idx=2
            e.g. for k=22 (the string is now 0010020030040050060070): num=8, digit_idx=0
        observe that num and digit_idx can then be directly computed:
            num       = (k-1)/3 + 1
            digit_idx = (k-1)%3

        observe that there are:
            9 positive integers with 1 digits
            90 positive integers with 2 digits
            900 positive integers with 3 digits
            ...
        then we can iterate the number of digits until we find the correct one:
            if   k <= 9*1:                num       = (k - 1)/1 + (1)
                                          digit_idx = (k - 1)%1
            elif k <= 9*1 + 90*2:         num       = (k-9*1 - 1)/2 + (1+9)
                                          digit_idx = (k-9*1 - 1)%2
            elif k <= 9*1 + 90*2 + 900*3: num       = (k-9*1-90*2 - 1)/3 + (1+9+90)
                                          digit_idx = (k-9*1-90*2 - 1)%3
            elif ...
        */
        long num = 1;
        long step = 9;
        int num_digits = 1;
        while (k > step * num_digits) {
            k -= step * num_digits;
            num += step;

            step *= 10;
            num_digits++;
        }
        auto [quot, rem] = ldiv(k - 1, num_digits);
        num += quot;
        int digit_idx = (int)rem;

        // extract the wanted digit
        // remember that digit_idx=0 means MSB
        for (int i = 0; i < (num_digits - 1 - digit_idx); i++) {
            num /= 10;
        }
        printf("%ld\n", num % 10);
    }
}
