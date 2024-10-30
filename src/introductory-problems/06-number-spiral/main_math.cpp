#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_TESTS;
    {
        std::cin >> NUM_TESTS;
    }

    unsigned x;
    unsigned y;
    while (NUM_TESTS--) {
        std::cin >> y >> x;
        // transform to 0-based (personal preference)
        y--;
        x--;

        auto const layer_idx = std::max(x, y);
        std::cout << ((layer_idx & 1)
                          // move from the smallest element at layer_idx (the bottom-left element) to (x,y)
                          ? (unsigned long)layer_idx * layer_idx + 1 + y + layer_idx - x
                          // move from the smallest element at layer_idx (the top-right element) to (x,y)
                          : (unsigned long)layer_idx * layer_idx + 1 + x + layer_idx - y)
                  << '\n';
    }
}