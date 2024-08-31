#ifndef __UTILS_H
#define __UTILS_H

#include <algorithm>
#include <concepts>
#include <ranges>
#include <vector>

// (ref.) [C++ template function, specify argument type of callback functor/lambda while still allow inlining?](https://stackoverflow.com/questions/61932900/c-template-function-specify-argument-type-of-callback-functor-lambda-while-st#comment109544863_61933163)
template <
    typename Return,
    typename Fn,
    typename... Args>
concept regular_invocable_returning = std::regular_invocable<Fn, Args...>
                                      && std::same_as<Return, std::invoke_result_t<Fn, Args...>>;

template <std::ranges::sized_range Range, typename KeyFn = std::identity>
    requires std::regular_invocable<KeyFn, std::ranges::range_value_t<Range>>
auto order_of_elements(
    Range &&range,
    KeyFn   key_fn = {},
    bool    reverse = false
) {
    using Key = std::invoke_result_t<KeyFn, std::ranges::range_value_t<Range>>;
    struct Pair {
        std::size_t id;
        Key         key;
    };

    auto ids_sorted_by_key = std::vector<Pair>(range.size());
    {
        for (std::size_t i = 0; i < range.size(); i++) {
            ids_sorted_by_key[i] = {i, key_fn(range[i])};
        }
        if (!reverse) {
            auto compare_fn = std::less<>{};
            std::ranges::sort(
                ids_sorted_by_key,
                [&compare_fn](auto const &lhs, auto const &rhs) { return compare_fn(lhs.key, rhs.key); }
            );
        } else {
            auto compare_fn = std::greater<>{};
            std::ranges::sort(
                ids_sorted_by_key,
                [&compare_fn](auto const &lhs, auto const &rhs) { return compare_fn(lhs.key, rhs.key); }
            );
        }
    }

    auto id_to_order = std::vector<std::size_t>(range.size());
    auto curr_order = 0;
    {
        id_to_order[ids_sorted_by_key[0].id] = curr_order;
        for (std::size_t i = 1; i < range.size(); i++) {
            if (ids_sorted_by_key[i].key != ids_sorted_by_key[i - 1].key) {
                curr_order++;
            }
            id_to_order[ids_sorted_by_key[i].id] = curr_order;
        }
    }
    return id_to_order;
}

#endif