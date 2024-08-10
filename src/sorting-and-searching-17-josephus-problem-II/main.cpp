#define VERSION_ORDERED_SET 1
#define VERSION_BLOCKED_VECTORS 2

#define VERSION VERSION_BLOCKED_VECTORS

#if VERSION == VERSION_ORDERED_SET
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    // (ref.) [Ordered Set and GNU C++ PBDS](https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/)
    __gnu_pbds::tree<int,
                     __gnu_pbds::null_type,
                     std::less<int>,
                     __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>
        childs;
    for (int i = 1; i <= n; i++) {
        childs.insert(i);
    }

    int child_idx = 0;
    for (int i = 0; i < n; i++) {
        child_idx = (child_idx + k) % (int)childs.size();
        auto it = childs.find_by_order(child_idx);
        printf("%d ", *it);
        childs.erase(it);
    }
    printf("\n");
}
#elif VERSION == VERSION_BLOCKED_VECTORS
#include <cstdio>
#include <vector>

int main() {
    // (ref.) [Is there an alternative solution to CSES Josephus Problem II?](https://codeforces.com/blog/entry/102198)

    /*
    BLOCK_SIZE can be fine-tuned.

    A smaller BLOCK_SIZE improves erasing (for moving fewer elements & being more cache-friendly),
    but at the cost of spending more time on searching the correct block,
    and vice versa.
    */
    constexpr int BLOCK_SIZE = 4096;

    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<int> child_blocks[(int)2e5 / BLOCK_SIZE + 1];
    int num_blocks = 1;
    child_blocks[0].reserve(BLOCK_SIZE);
    for (int i = 1; i <= n; i++) {
        child_blocks[num_blocks - 1].push_back(i);
        if (child_blocks[num_blocks - 1].size() >= BLOCK_SIZE) {
            num_blocks++;
            child_blocks[num_blocks - 1].reserve(BLOCK_SIZE);
        }
    }

    int child_idx = 0;
    int block_idx = 0;
    for (int i = 0; i < n; i++) {
        child_idx += k % (n - i);
        while (child_idx >= child_blocks[block_idx].size()) {
            child_idx -= child_blocks[block_idx].size();
            block_idx++;
            if (block_idx >= num_blocks) {
                block_idx = 0;
            }
        }
        printf("%d ", child_blocks[block_idx][child_idx]);
        child_blocks[block_idx].erase(child_blocks[block_idx].begin() + child_idx);
    }
    printf("\n");
}
#endif