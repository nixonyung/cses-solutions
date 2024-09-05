set ignore-comments

# (ref.) [docker pull shows "What's Next? docker scout quickview debian" (use DOCKER_CLI_HINTS to disable)](https://github.com/docker/for-mac/issues/6904)
export DOCKER_CLI_HINTS := "false"

DOCKER_IMAGE_TAG := "cses-solutions"
DOCKER_IMAGE_FILE := "./docker/Dockerfile"
DOCKER_RUN_COMMAND := "docker run -it --volume " + justfile_directory() + ":/src:ro --entrypoint just " + DOCKER_IMAGE_TAG
DOCKER_JUSTFILE := "./docker/justfile"

_build_docker:
    docker build -t {{DOCKER_IMAGE_TAG}} -f {{DOCKER_IMAGE_FILE}} .


test-draft: _build_docker
    {{DOCKER_RUN_COMMAND}} -f {{DOCKER_JUSTFILE}} test-draft

test solution_file test_id=("all"): _build_docker
    {{DOCKER_RUN_COMMAND}} -f {{DOCKER_JUSTFILE}} test {{solution_file}} {{test_id}}