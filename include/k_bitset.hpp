#ifndef __K_BITSET_H
#define __K_BITSET_H

#include "primitives.hpp"
#include <vector>

template <U8 K>
    requires(K < 8) // you should be using standard vectors if K >= 8, e.g. vector<unsigned char>, vector<u32>, ...
struct KBitset {
    // (ref.) [std::vector<bool, Alloc>::reference](https://en.cppreference.com/w/cpp/container/vector_bool/reference)
    using ConstReference = U32;
    struct Reference {
        friend struct KBitset;

        operator ConstReference() const { return parent.get(pos); }

        Reference &operator=(U8 val) {
            parent.set(pos, val);
            return *this;
        }

      private:
        KBitset &parent;
        USize pos;

        Reference(KBitset &parent, USize pos)
            : parent(parent),
              pos(pos) {
        }
    };

    KBitset(USize n)
        : c(n * K, false),
          n(n) {
    }
    KBitset(USize n, U8 val)
        : c(n * K),
          n(n) {
        for (USize i = 0; i < n; i++) set(i, val);
    }

    auto const size() const { return n; }

    Reference operator[](USize pos) {
        return {*this, pos};
    }
    auto operator[](USize pos) const {
        return get(pos);
    }

  private:
    std::vector<bool> c;
    USize n;

    auto get(USize pos) const {
        U32 val = 0; // use u32 so that the result will be printed as an integer instead of a character
        for (int i = 0; i < K; i++) val += c[pos * K + i] * (1 << i);
        return val;
    }

    void set(USize pos, U8 val) {
        // only take K LSBs from val
        // put LSB before MSB
        for (int i = 0; i < K; i++) c[pos * K + i] = val & (1 << i);
    }
};

#endif