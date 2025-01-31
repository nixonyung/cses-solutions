FROM debian:sid-slim

# [Docker, can you cache apt-get package installs?](https://stackoverflow.com/questions/66808788/docker-can-you-cache-apt-get-package-installs)
# [Using a pip cache directory in docker builds](https://stackoverflow.com/questions/58018300/using-a-pip-cache-directory-in-docker-builds)
RUN --mount=type=cache,target=/var/lib/apt/lists,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/root/.cache/pip \
    rm -f /etc/apt/apt.conf.d/docker-clean && \
    apt-get update && apt-get install -y --no-install-recommends \
        wget ca-certificates \
        just \
        g++-14 \
        gdb \
        valgrind \
        python3 python3-graphviz && \
    wget -P ~ https://github.com/cyrus-and/gdb-dashboard/raw/master/.gdbinit