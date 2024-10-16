#ifndef __IO_H
#define __IO_H

#include <iostream>

static inline void enable_fast_io() {
    // (ref.) [Fast Input & Output](https://usaco.guide/general/fast-io?lang=cpp)
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

template <typename T>
static inline auto read() -> T {
    T val;
    std::cin >> val;
    return val;
}

#endif