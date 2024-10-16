# CSES Solutions

(WIP)

## Prerequisites

- [Docker](https://docs.docker.com/engine/install/)
- [just](https://github.com/casey/just)

## Getting Started

- study a problem in [CSES](https://cses.fi/problemset/)
- download test cases, put under `src/<PROBLEM>/tests`
- run `just test src/<PROBLEM>`
  - e.g. `just test src/introductory-problems-01-weird-algorithm`
- helpers:
  - run `just debug src/<PROBLEM>/<SOLUTION> <TEST_ID>`
    - adding breakpoints:
      - `b <LINE_NUMBER>` / `b <FUNCTION>` to add breakpoint
      - `info breakpoints` to list breakpoints
      - `d <BREAKPOINT_NUM>` to delete breakpoint
    - running the program:
      - `r </.in` to start debugging
      - `n` to step 1 line
      - `c` to continue to next breakpoint
      - `step` to step into function
      - `q` to quit
    - debugging:
      - `p <VARIABLE>` to print variable
      - `display <VARIABLE>` to print variable at every step
  - run `just visualize_graph src/<PROBLEM>/tests/<TEST_ID>.in`
  - run `just make_submission src/<PROBLEM>/<SOLUTION>`

## References

- [Jonathan-Uy/CSES-Solutions](https://github.com/Jonathan-Uy/CSES-Solutions)
- [mrsac7/CSES-Solutions](https://github.com/mrsac7/CSES-Solutions)
- [Algorithms for Competitive Programming](https://cp-algorithms.com/)
- [Competitive Programmer's Handbook](https://cses.fi/book/book.pdf)
- [Fast Input & Output](https://usaco.guide/general/fast-io?lang=cpp)
- [Practical Optimizations](https://youtu.be/NAVbI1HIzCE)
- [How can I be sure a routine is taking advantage of (N)RVO?](https://stackoverflow.com/questions/9621720/how-can-i-be-sure-a-routine-is-taking-advantage-of-nrvo)
- [C++20 Range Adaptors and Range Factories](https://brevzin.github.io/c++/2021/02/28/ranges-reference/)
