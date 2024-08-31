#include "../../lib/cses_io.hpp"
#include <algorithm>
#include <limits>

int main() {
    cses::enable_fast_io();

    auto n = cses::read<int>();

    auto ans = std::numeric_limits<long>::min();
    {
        auto curr_sum = 0L;
        while (n--) {
            curr_sum += cses::read<int>();
            ans = std::max(ans, curr_sum);
            /*
            if curr_sum > 0:
                keep curr_sum, as it may constitute to a larger subarray sum
            else:
                reset curr_sum, as a negative curr_sum will only make the subarray sum smaller
            */
            curr_sum = (curr_sum > 0) ? curr_sum : 0;
        }
    }
    std::cout << ans << '\n';
}