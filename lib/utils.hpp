#ifndef __UTILS_H
#define __UTILS_H

#include <algorithm>
#include <bit>
#include <concepts>
#include <functional>
#include <iostream>
#include <limits>
#include <ranges>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using uint = unsigned int;
using ulong = unsigned long;
using std::string;
using std::views::iota;

static void enable_fast_io() {
    // (ref.) [Fast Input & Output](https://usaco.guide/general/fast-io?lang=cpp)
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

template <typename T>
auto read() -> T {
    T val;
    std::cin >> val;
    return val;
}

template <uint MOD = (int)1e9 + 7>
static auto int_pow(ulong base, uint pow) {
    ulong ans = 1;
    // (ref.) [Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html)
    {
        while (pow > 0) {
            if (pow & 1) {
                ans = (ans * base) % MOD;
            }
            base = (base * base) % MOD;
            pow >>= 1;
        }
    }
    return ans;
}

/*
given an array, return a new array storing the order of each element

e.g.
    given  `[0.10,20,40,40,30]`,
    return `[0, 1, 2, 4, 4, 3]`
*/
template <std::ranges::sized_range Range, typename KeyFn = std::identity>
    requires std::ranges::common_range<Range> &&
             std::ranges::sized_range<Range> &&
             std::ranges::random_access_range<Range> &&
             std::regular_invocable<KeyFn, std::ranges::range_value_t<Range>> &&
             std::equality_comparable<std::invoke_result_t<KeyFn, std::ranges::range_value_t<Range>>>
auto find_order_of_elements(
    Range &&range,
    KeyFn key_fn = {},
    bool reverse = false
) {
    struct Pair {
        size_t id;
        std::invoke_result_t<KeyFn, std::ranges::range_value_t<Range>> key;
    };

    auto pairs_sorted_by_key = std::vector<Pair>(range.size());
    {
        for (auto i : iota(0UL, range.size())) {
            pairs_sorted_by_key[i] = {i, key_fn(range[i])};
            i++;
        }
        if (!reverse) {
            std::ranges::sort(
                pairs_sorted_by_key,
                [](auto const &lhs, auto const &rhs) { return lhs.key < rhs.key; }
            );
        } else {
            std::ranges::sort(
                pairs_sorted_by_key,
                [](auto const &lhs, auto const &rhs) { return lhs.key > rhs.key; }
            );
        }
    }

    auto id_to_order = std::vector<size_t>(range.size());
    {
        size_t curr_order = 0;
        id_to_order[pairs_sorted_by_key[0].id] = curr_order;
        for (auto i : iota(1UL, range.size())) {
            curr_order += pairs_sorted_by_key[i].key != pairs_sorted_by_key[i - 1].key;
            id_to_order[pairs_sorted_by_key[i].id] = curr_order;
        }
    }
    return id_to_order;
}

// Generatlized radix sort that support any power of 2 as the radix.
template <
    /*
    RADIX_BIT_WIDTH and MAX_NUM_DIGITS together control the supported input range,
    i.e. Radix sort can sort integers within range [0, 2^(RADIX_BIT_WIDTH * MAX_NUM_DIGITS)).

    Default RADIX_BIT_WIDTH = 15 and MAX_NUM_DIGITS = 2 so that it can sort integers <= 1e9.
    */
    auto RADIX_BIT_WIDTH = 15,
    auto MAX_NUM_DIGITS = 2,
    std::ranges::range Range,
    typename KeyFn = std::identity>
    requires std::ranges::common_range<Range> &&
             std::ranges::sized_range<Range> &&
             std::ranges::random_access_range<Range> &&
             std::regular_invocable<KeyFn, std::ranges::range_value_t<Range>> &&
             std::unsigned_integral<std::remove_reference_t<std::invoke_result_t<KeyFn, std::ranges::range_value_t<Range>>>> &&
             (
                 // ensure `1 << RADIX_BIT_WIDTH` is valid,
                 // and you probably don't want to allocate `(1 << RADIX_BIT_WIDTH) * sizeof(size_t)` memory
                 RADIX_BIT_WIDTH < 32
             ) &&
             (
                 // ensure `val >> (RADIX_BIT_WIDTH * digit_idx)` is valid
                 RADIX_BIT_WIDTH * (MAX_NUM_DIGITS - 1) <
                 std::numeric_limits<std::remove_reference_t<std::invoke_result_t<KeyFn, std::ranges::range_value_t<Range>>>>::digits
             )
void radix_sort(Range &&range, KeyFn key_fn = {}) {
    // (ref.) [Radix sort vs Counting sort vs Bucket sort. What's the difference?](https://stackoverflow.com/questions/14368392/radix-sort-vs-counting-sort-vs-bucket-sort-whats-the-difference)
    // (ref.) [Radix Sort - Data Structures and Algorithms Tutorials](https://www.geeksforgeeks.org/radix-sort/)

    static auto buckets = std::vector<size_t>(1 << RADIX_BIT_WIDTH);
    static auto get_digit = [](
                                std::remove_reference_t<std::invoke_result_t<KeyFn, std::ranges::range_value_t<Range>>> val,
                                uint digit_idx
                            ) {
        return (val >> (RADIX_BIT_WIDTH * digit_idx)) & ((1 << RADIX_BIT_WIDTH) - 1);
    };

    {
        std::vector<size_t> order_of_elements(range.size());
        // sort from LSB to MSB
        for (auto digit_idx : iota(0, MAX_NUM_DIGITS)) {
            std::ranges::fill(buckets, 0);
            for (auto const &val : range) {
                buckets[get_digit(key_fn(val), digit_idx)]++;
            }
            // update buckets[i] so that `buckets[i]-1` is the sorted index of the last element with lower_radix == i
            for (auto i : iota(1UL, buckets.size())) {
                buckets[i] += buckets[i - 1];
            }
            for (auto i : iota(0UL, range.size()) | std::views::reverse) {
                order_of_elements[i] = --buckets[get_digit(key_fn(range[i]), digit_idx)];
            }
            // (ref.) [Reorder an array according to given indexes - Cyclic Sort](https://www.geeksforgeeks.org/reorder-a-array-according-to-given-indexes/)
            for (auto i : iota(0UL, range.size())) {
                while (order_of_elements[i] != i) {
                    std::swap(range[i], range[order_of_elements[i]]);
                    std::swap(order_of_elements[i], order_of_elements[order_of_elements[i]]);
                }
            }
        }
    }
}

/*
A generalized variation of `std::lower_bound` that runs on arbitrary integer range [0,size).

Assumption:
    Given `size`, if there is at least 1 position `pos` in [0, size) where `is_valid(pos)` is true,
    then [0, pos) are all invalid and [pos, size) are all valid.

This function do the following:
    - if there is no such `pos`:
        => return `size`
    - else:
        => find and return `pos`
*/
template <typename ValidFn>
    requires std::regular_invocable<ValidFn, size_t> &&
             std::same_as<bool, std::invoke_result_t<ValidFn, size_t>>
auto find_first_valid(size_t bound, ValidFn is_valid) {
    if (
        bound == 0 ||
        !is_valid(bound - 1) // optimization (based on the assumption): early exit if there is no valid `pos`
    ) {
        return bound;
    }

    size_t pos = 0;
    {
        for (auto step = 1UL << (std::numeric_limits<size_t>::digits - 1 - std::countl_zero(bound - 1));
             step > 0;
             step >>= 1) {
            // find last invalid pos
            if (pos + step < bound && !is_valid(pos + step)) {
                pos += step;
            }
        }
        // return first valid pos
        pos++;
    }
    return pos;
}

#endif