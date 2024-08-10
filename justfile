set ignore-comments

CC := "g++-14"
CPP_VERSION := "c++20"
# (ref.) [My favorite C compiler flags during development](https://nullprogram.com/blog/2023/04/29/#summary)
FLAGS := "-O2 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap"
TIMEOUT := "2s"

DOCKER_IMAGE_TAG := "cses-solutions"
# (ref.) [docker pull shows "What's Next? docker scout quickview debian" (use DOCKER_CLI_HINTS to disable)](https://github.com/docker/for-mac/issues/6904)
export DOCKER_CLI_HINTS := "false"
BUILD_SOLUTION_OUT_FILE := "/out/main"


debug problem test_idx: _build_docker
    docker run -t \
    --volume {{justfile_directory()}}:/app:ro \
    {{DOCKER_IMAGE_TAG}} _debug {{problem}} {{test_idx}}

test problem: _build_docker
    docker run -t \
    --volume {{justfile_directory()}}:/app:ro \
    {{DOCKER_IMAGE_TAG}} _test {{problem}}


_build_docker:
    docker build -t {{DOCKER_IMAGE_TAG}} .

_build_solution problem:
    mkdir -p /out
    {{CC}} -std={{CPP_VERSION}} {{FLAGS}} ./{{problem}}/main.cpp -o {{BUILD_SOLUTION_OUT_FILE}}

_debug problem test_idx: (_build_solution problem)
    {{BUILD_SOLUTION_OUT_FILE}} <./{{problem}}/tests/{{test_idx}}.in

_test problem: (_build_solution problem)
    #!/usr/bin/env bash
    set -euxo pipefail
    # (ref.) [how to handle bash * matching when there are no matches?](https://superuser.com/questions/519374/how-to-handle-bash-matching-when-there-are-no-matches)
    shopt -s nullglob

    test_indexs=()
    # (ref.) [Globbing for only files in Bash](https://stackoverflow.com/questions/20745656/globbing-for-only-files-in-bash)
    for input in {{problem}}/tests/*.in; do
        # (ref.) [Extract filename and extension in Bash](https://stackoverflow.com/questions/965053/extract-filename-and-extension-in-bash)
        filename="$(basename $input)"
        index="${filename%.*}"
        # (ref.) [Add a new element to an array without specifying the index in Bash](https://stackoverflow.com/questions/1951506/add-a-new-element-to-an-array-without-specifying-the-index-in-bash)
        test_indexs+=("$index")
    done

    function check() {
        # (ref.) [How do I compare a command output to a text file?](https://unix.stackexchange.com/questions/530124/how-do-i-compare-a-command-output-to-a-text-file)
        if diff --brief \
            <(timeout {{TIMEOUT}} {{BUILD_SOLUTION_OUT_FILE}} <{{problem}}/tests/$1.in) \
            {{problem}}/tests/$1.out \
            >/dev/null
        then
            echo "test $1 ok"
        else
            echo "test $1 failed"
        fi
    }
    export -f check

    # (ref.) [How to run given function in Bash in parallel?](https://stackoverflow.com/questions/17307800/how-to-run-given-function-in-bash-in-parallel)
    time parallel check ::: "${test_indexs[@]}"