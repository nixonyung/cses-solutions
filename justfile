set ignore-comments

PROJECT_NAME := "cses-solutions"

# (ref.) [creating a Dockerfile that grants ownership of any created files to the host user instead of root [duplicate]](https://stackoverflow.com/a/79309138)
# (ref.) [How to increase stack size of c++ in ubuntu?](https://codeforces.com/blog/entry/63140)
# (ref.) {如何调整 docker 下 linux 的 ulimit 大小设置？}(https://gorden5566.com/post/1089.html)
DOCKER_RUN := "docker run --rm " + \
    "--workdir /usr/local/src " + \
    "--volume $(pwd):/usr/local/src " + \
    "--user $(id -u):$(id -g) " + \
    "--ulimit stack=-1 "

# (ref.) [My favorite C compiler flags during development](https://nullprogram.com/blog/2023/04/29/)
# (ref.) [Whether to use -pedantic flag in g++ or not?](https://softwareengineering.stackexchange.com/questions/88532/whether-to-use-pedantic-flag-in-g-or-not)
GCC := "g++-14 " + \
    "-std=c++20 " + \
    "-I ./include " + \
    "-o ./out/main " + \
    "-pedantic -Wall -Wextra "

_build:
    docker build -t {{PROJECT_NAME}} .
    mkdir -p ./out

cp-tests source target:
    unzip {{source}} -d {{target}}/tests

run-draft: _build
    {{DOCKER_RUN}} -t {{PROJECT_NAME}} {{GCC}} -O0 ./draft.cpp
    ./out/main

test solution_file test_id="": _build
    # (ref.) [CSES - Languages](https://cses.fi/howto/)
    {{DOCKER_RUN}} -t {{PROJECT_NAME}} {{GCC}} -O2 {{solution_file}}
    {{DOCKER_RUN}} -t {{PROJECT_NAME}} python3 ./scripts/test.py {{solution_file}} {{test_id}}

gdb solution_file test_id: _build
    # (ref.) [What's the difference between a compiler's `-O0` option and `-Og` option?](https://stackoverflow.com/questions/63386189/whats-the-difference-between-a-compilers-o0-option-and-og-option)
    {{DOCKER_RUN}} -t {{PROJECT_NAME}} {{GCC}} -O0 -ggdb {{solution_file}}
    # (ref.) [warning: Error disabling address space randomization: Operation not permitted](https://stackoverflow.com/questions/35860527/warning-error-disabling-address-space-randomization-operation-not-permitted)
    # (ref.) [How to use gdb with input redirection?](https://stackoverflow.com/a/4758218)
    {{DOCKER_RUN}} -it --security-opt seccomp=unconfined {{PROJECT_NAME}} gdb --quiet -ex "set args <./`dirname {{solution_file}}`/tests/{{test_id}}.in" ./out/main

valgrind solution_file test_id: _build
    {{DOCKER_RUN}} -t {{PROJECT_NAME}} {{GCC}} -O0 -g {{solution_file}}
    # (ref.) [Memchk (valgrind) reporting inconsistent results in different docker hosts](https://stackoverflow.com/questions/75292406/memchk-valgrind-reporting-inconsistent-results-in-different-docker-hosts)
    {{DOCKER_RUN}} -i --ulimit nofile=1024 {{PROJECT_NAME}} valgrind --leak-check=full ./out/main <./`dirname {{solution_file}}`/tests/{{test_id}}.in

make_submission solution_file: _build
    {{DOCKER_RUN}} -t {{PROJECT_NAME}} python3 ./scripts/make_submission.py {{solution_file}}

visualize_graph test_file: _build
    {{DOCKER_RUN}} -t {{PROJECT_NAME}} python3 ./scripts/visualize_graph.py {{test_file}}