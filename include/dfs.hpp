#ifndef __DFS_H_
#define __DFS_H_

#include "k_bitset.hpp"
#include "primitives.hpp"
#include <stack>
#include <vector>

// helper container to run DFS, i.e. iterate nodes without revisiting
template <bool ENABLE_BACKTRACKING = true>
struct DFS {
    enum Phase : U8 {
        EXPLORE,      // side property: an EXPLORE node is never visited
        BACKTRACKING, // side property: when visiting a BACKTRACKING node, its adjs must be all DONE
        DONE,         // side property: when visiting a DONE node, its adjs must be all DONE
    };

    struct ToVisit {
        U32 id;
        Phase phase;
    };

    DFS(U32 n, std::vector<std::vector<U32>> const &adjss)
        : adjss(adjss),
          s(),
          phases(n, Phase::EXPLORE) {
    }

    auto push(U32 id) { s.push(id); }

    ToVisit pop() {
        U32 curr;
        do {
            if (s.empty()) return {UINT_MAX, Phase::DONE};
            curr = s.top();
            s.pop();
        } while (phases[curr] == Phase::DONE);

        if (phases[curr] == Phase::BACKTRACKING) {
            phases[curr] = Phase::DONE;
            return {curr, Phase::BACKTRACKING};
        }

        if (ENABLE_BACKTRACKING) {
            phases[curr] = Phase::BACKTRACKING;
            s.push(curr);
        } else {
            phases[curr] = Phase::DONE;
        }
        for (auto const &adj : adjss[curr]) {
            if (phases[adj] == Phase::EXPLORE) s.push(adj);
        }
        return {curr, Phase::EXPLORE};
    }

  private:
    std::vector<std::vector<U32>> const &adjss;
    std::stack<U32> s;
    KBitset<2> phases;
};

#endif