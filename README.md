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
- run `just make_submission src/<PROBLEM>/<SOLUTION>` and submit `./out/submission.cpp`

### Helper Commands

- run a single test case (with outputs):
  - run `just test src/<PROBLEM>/<SOLUTION> <TEST_ID>`
- run a single test case with valgrind:
  - run `just valgrind src/<PROBLEM>/<SOLUTION> <TEST_ID>`
- start debugger (e.g. to deal with "segmentation faults"):
  - run `just debug src/<PROBLEM>/<SOLUTION> <TEST_ID>`
    - adding breakpoints:
      - `b <LINE_NUMBER>` / `b <FUNCTION>` to add breakpoint
      - `info breakpoints` to list breakpoints
      - `d <BREAKPOINT_NUM>` to delete breakpoint
    - running the program:
      - `r </app/.in` to start debugging
      - `n` to step 1 line
        - `n <COUNT>` to step n lines
      - `c` to continue to next breakpoint
        - `c <COUNT>` to break after n breakpoints
      - `step` to step into function
      - `q` to quit
    - debugging:
      - `p <VARIABLE>` to print variable
      - `display <VARIABLE>` to print variable at every step
      - `bt` to print the call stack
- visualizing graph problem input (may not work for test cases with different format):
  - run `just visualize_graph src/<PROBLEM>/tests/<TEST_ID>.in`

## References

- others' solutions:
  - [Jonathan-Uy/CSES-Solutions](https://github.com/Jonathan-Uy/CSES-Solutions)
  - [mrsac7/CSES-Solutions](https://github.com/mrsac7/CSES-Solutions)
  - [CSES Problemset Editorials (almost all section editorial collection)](https://codeforces.com/blog/entry/83343)
- Competitive Programming resources:
  - [Algorithms for Competitive Programming](https://cp-algorithms.com/)
  - [Competitive Programmer's Handbook](https://cses.fi/book/book.pdf)
  - [Fast Input & Output](https://usaco.guide/general/fast-io?lang=cpp)
- optimization guidelines:
  - [Practical Optimizations](https://youtu.be/NAVbI1HIzCE)
  - [How can I be sure a routine is taking advantage of (N)RVO?](https://stackoverflow.com/questions/9621720/how-can-i-be-sure-a-routine-is-taking-advantage-of-nrvo)
  - [Goto out of a block: do destructors get called?](https://stackoverflow.com/questions/3179936/goto-out-of-a-block-do-destructors-get-called)
