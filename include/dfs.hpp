#ifndef __DFS_H_
#define __DFS_H_

#include "k_bitset.hpp"
#include "primitives.hpp"
#include <stack>
#include <vector>

// helper container to run DFS, i.e. iterate nodes without revisiting
template <bool ENABLE_BACKTRACKING = true>
struct DFS {
    using ID = U32;
    enum Phase : U8 {
        EXPLORE,      // side property: an EXPLORE node is never visited
        BACKTRACKING, // side property: when visiting a BACKTRACKING node, its `nexts` must be all DONE
        DONE,         // side property: when visiting a DONE node, its `nexts` must be all DONE
    };

    struct ToVisit {
        ID id;
        Phase phase;
    };

    DFS(USize n, std::vector<std::vector<ID>> const &nextss)
        : nextss(nextss),
          s(),
          phases(n, Phase::EXPLORE) {
    }

    auto push(ID id) { s.push(id); }

    ToVisit pop() {
        if (s.empty()) return {UINT_MAX, Phase::DONE};
        ID curr = s.top();
        while (phases[curr] == Phase::DONE) {
            s.pop();
            if (s.empty()) return {UINT_MAX, Phase::DONE};
            curr = s.top();
        }

        if (phases[curr] == Phase::BACKTRACKING) {
            phases[curr] = Phase::DONE;
            return {curr, Phase::BACKTRACKING};
        }

        if (ENABLE_BACKTRACKING) {
            phases[curr] = Phase::BACKTRACKING;
        } else {
            phases[curr] = Phase::DONE;
            s.pop();
        }
        for (auto const &next : nextss[curr]) {
            if (phases[next] == Phase::EXPLORE) s.push(next);
        }
        return {curr, Phase::EXPLORE};
    }

  private:
    std::vector<std::vector<ID>> const &nextss;
    std::stack<ID> s;
    KBitset<2> phases;
};

#endif