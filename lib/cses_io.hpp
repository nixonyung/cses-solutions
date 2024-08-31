#ifndef __CSES_IO_H
#define __CSES_IO_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

namespace cses {
// (ref.) [Fast Input & Output](https://usaco.guide/general/fast-io?lang=cpp#fast)
static auto enable_fast_io() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

template <typename T>
auto read() {
    T val;
    std::cin >> val;
    return val;
}

template <typename... Args>
auto read_tuple() {
    // (ref.) [build tuple using variadic templates](https://stackoverflow.com/questions/10014713/build-tuple-using-variadic-templates)
    return std::make_tuple(read<Args>()...);
}

template <typename T>
auto read_vector(std::size_t n) {
    auto v = std::vector<T>(n);
    // (ref.) [How to store user input (cin) into a Vector?](https://stackoverflow.com/questions/8377660/how-to-store-user-input-cin-into-a-vector)
    std::copy_n(std::istream_iterator<T>(std::cin), n, v.begin());
    return v;
}

template <typename T>
auto read_vector_with_ids(std::size_t n) {
    struct Input {
        std::size_t id;
        T           val;

        auto &operator=(T val) {
            this->val = val;
            return *this;
        }
    };

    auto v = std::vector<Input>(n);
    // (ref.) [How to store user input (cin) into a Vector?](https://stackoverflow.com/questions/8377660/how-to-store-user-input-cin-into-a-vector)
    std::copy_n(std::istream_iterator<T>(std::cin), n, v.begin());
    for (std::size_t i = 0; auto &el : v) {
        el.id = i;
        i++;
    }
    return v;
}

template <typename T>
auto read_set(std::size_t n) {
    auto s = std::set<T>();
    // (ref.) [std::back_inserter for a std::set?](https://stackoverflow.com/questions/908272/stdback-inserter-for-a-stdset)
    std::copy_n(std::istream_iterator<T>(std::cin), n, std::inserter(s, s.begin()));
    return s;
}

template <typename T>
auto read_multiset(std::size_t n) {
    auto s = std::multiset<T>();
    // (ref.) [std::back_inserter for a std::set?](https://stackoverflow.com/questions/908272/stdback-inserter-for-a-stdset)
    std::copy_n(std::istream_iterator<T>(std::cin), n, std::inserter(s, s.begin()));
    return s;
}

template <std::ranges::range Range>
auto print_range(
    Range            &&range,
    std::string const &sep = " ",
    std::string const &end = "\n"
) {
    // intentionally print one trailing sep
    std::ranges::copy(
        range,
        std::ostream_iterator<std::ranges::range_value_t<Range>>(std::cout, sep.c_str())
    );
    std::cout << end;
}
} // namespace cses

#endif