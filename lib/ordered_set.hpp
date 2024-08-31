#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// (ref.) [Ordered Set and GNU C++ PBDS](https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/)
template <typename T, typename CompareFn = std::less<>>
using OrderedSet = __gnu_pbds::tree<
    T,
    __gnu_pbds::null_type,
    CompareFn,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;