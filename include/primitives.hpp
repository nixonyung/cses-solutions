#ifndef __PRIMITIVES_H
#define __PRIMITIVES_H

#include <climits> // provides INT_MAX, LONG_MAX, UINT_MAX, ULONG_MAX
#include <cstdint>
#include <type_traits>

// personal preference: better primitive integer types that are more precise and "make sense"
// (ref.) [HolyC - Types](https://holyc-lang.com/docs/language-spec/learn-types)
// (ref.) [Zig - Primitive Types](https://ziglang.org/documentation/master/#Primitive-Types)
using U8 = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;
using I8 = int8_t;
using I16 = int16_t;
using I32 = int32_t;
using I64 = int64_t;
using USize = std::size_t;
using ISize = std::make_signed_t<std::size_t>;

#define UNARY_FN(arg) [](auto const &arg)
#define BINARY_FN(arg1, arg2) [](auto const &arg1, auto const &arg2)

#endif