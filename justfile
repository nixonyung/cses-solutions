set ignore-comments

# (ref.) [docker pull shows "What's Next? docker scout quickview debian" (use DOCKER_CLI_HINTS to disable)](https://github.com/docker/for-mac/issues/6904)
export DOCKER_CLI_HINTS := "false"

DOCKER_IMAGE_TAG := "cses-solutions"
DOCKER_IMAGE_FILE := if os() == "linux" { "./docker/linux.Dockerfile" } else { "./docker/Dockerfile" }
DOCKER_JUSTFILE := "./docker/justfile"
# (ref.) [How to increase stack size of c++ in ubuntu?](https://codeforces.com/blog/entry/63140)
# (ref.) {如何调整 docker 下 linux 的 ulimit 大小设置？}(https://gorden5566.com/post/1089.html)
# (ref.) [Memchk (valgrind) reporting inconsistent results in different docker hosts](https://stackoverflow.com/questions/75292406/memchk-valgrind-reporting-inconsistent-results-in-different-docker-hosts)
# (ref.) [warning: Error disabling address space randomization: Operation not permitted](https://stackoverflow.com/questions/35860527/warning-error-disabling-address-space-randomization-operation-not-permitted)
DOCKER_RUN_COMMAND := "docker run -it" \
    + " --volume " + justfile_directory() + ":/repo:ro" \
    + " --volume " + justfile_directory() + "/out:/out:rw" \
    + " --ulimit stack=268435456" \
    + " --ulimit nofile=1024" \
    + " --cap-add=SYS_PTRACE --security-opt seccomp=unconfined" \
    + " " + DOCKER_IMAGE_TAG + " -f " + DOCKER_JUSTFILE


_build_docker:
    docker build -t {{DOCKER_IMAGE_TAG}} -f {{DOCKER_IMAGE_FILE}} --build-arg USER_ID=`id -u` --build-arg GROUP_ID=`id -g` .
    mkdir -p ./out

run-draft: _build_docker
    {{DOCKER_RUN_COMMAND}} run-draft

test solution_file test_id=("all"): _build_docker
    {{DOCKER_RUN_COMMAND}} test {{solution_file}} {{test_id}}

test-all: _build_docker
    #!/usr/bin/env bash
    set -euxo pipefail
    for solution_file in src/**/**/*.cpp; do
        {{DOCKER_RUN_COMMAND}} test $solution_file "all"
    done

debug solution_file test_id: _build_docker
    {{DOCKER_RUN_COMMAND}} debug {{solution_file}} {{test_id}}

valgrind solution_file test_id: _build_docker
    {{DOCKER_RUN_COMMAND}} valgrind {{solution_file}} {{test_id}}

make_submission solution_file: _build_docker
    {{DOCKER_RUN_COMMAND}} make_submission {{solution_file}}

visualize_graph test_file: _build_docker
    {{DOCKER_RUN_COMMAND}} visualize_graph {{test_file}}