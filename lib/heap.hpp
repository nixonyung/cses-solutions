#ifndef __HEAP_H
#define __HEAP_H

#include <concepts>
#include <functional>
#include <queue>
#include <vector>

template <typename T, typename CompareFn = std::greater<>>
    requires std::predicate<CompareFn, T, T>
auto heap(CompareFn = {}) {
    return std::priority_queue<
        T,
        std::vector<T>,
        CompareFn>();
}

#endif