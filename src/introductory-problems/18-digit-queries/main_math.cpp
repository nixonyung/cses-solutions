#include <cmath>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_TESTS;
    {
        std::cin >> NUM_TESTS;
    }

    unsigned long pos;
    while (NUM_TESTS--) {
        std::cin >> pos;

        /*
        Given pos, we can find the answer by trying to find `num` and `digit_idx` (digit_idx=0 means MSB)
            e.g. for pos=7 (the string is 1234567)              => num=7,  digit_idx=0
            e.g. for pos=19 (the string is 1234567891011121314) => num=14, digit_idx=1

        Consider a modified problem where the number of digits is fixed to 3 by zero-padding:
            e.g. for pos=19 (the string is now 0010020030040050060):    num=7, digit_idx=0
            e.g. for pos=20 (the string is now 00100200300400500600):   num=7, digit_idx=1
            e.g. for pos=21 (the string is now 001002003004005006007):  num=7, digit_idx=2
            e.g. for pos=22 (the string is now 0010020030040050060070): num=8, digit_idx=0
        then `num` and `digit_idx` can then be directly computed:
            num       = (pos - 1)/3 + 1
            digit_idx = (pos - 1)%3

        Observe that the number of digits in integers has the following pattern:
            there are 9 positive integers with 1 digits
            there are 90 positive integers with 2 digits
            there are 900 positive integers with 3 digits
            ...
        then we can find `num` and `digit_idx` based on pos:
            if   pos <= 9*1:                num       = (pos          - 1)/1 + (1)
                                            digit_idx = (pos          - 1)%1
            elif pos <= 9*1 + 90*2:         num       = (pos-9*1      - 1)/2 + (1+9)
                                            digit_idx = (pos-9*1      - 1)%2
            elif pos <= 9*1 + 90*2 + 900*3: num       = (pos-9*1-90*2 - 1)/3 + (1+9+90)
                                            digit_idx = (pos-9*1-90*2 - 1)%3
            elif ...
        This can be better implemented as a "scan", i.e. modifying some states as we iterate the intervals of pos
        */
        unsigned long num = 1;
        unsigned long step = 9; // step of `num`
        unsigned num_digits = 1;
        while (pos > step * num_digits) {
            pos -= step * num_digits;
            num += step;
            step *= 10;
            num_digits++;
        }
        auto const [delta_num, digit_idx] = std::ldiv(pos - 1, num_digits);
        num += delta_num;
        // extract the wanted digit (note that digit_idx=0 means MSB)
        std::cout << (num / (long)std::pow(10, num_digits - 1 - digit_idx)) % 10 << '\n';
    }
}
