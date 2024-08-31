#define VERSION_SET 1
#define VERSION_VECTOR 2

#define VERSION VERSION_VECTOR

#include "../../lib/cses_io.hpp"

int main() {
    cses::enable_fast_io();

    /*
    implementations that won't work:
        - store a flag for all x to indicate if it has appeared
            => x <= 1e9 is too large
    */

    auto n = cses::read<int>();

#if VERSION == VERSION_SET
    auto s = cses::read_set<int>(n);
    std::cout << s.size() << '\n';
#elif VERSION == VERSION_VECTOR
    auto vals = cses::read_vector<int>(n);
    std::ranges::sort(vals);
    auto ans = 1;
    for (auto i = 0; i < n - 1; i++) {
        if (vals[i] != vals[i + 1]) {
            ans++;
        }
    }
    std::cout << ans << '\n';
#endif
}