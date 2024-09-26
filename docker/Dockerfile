FROM debian:sid-slim

# (ref.) [Installing GEF - Prerequisites](https://hugsy.github.io/gef/install/#prerequisites)
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ca-certificates wget \
        g++-14 \
        gdb \
        just \
        parallel \
        time \
    && rm -rf /var/lib/apt/lists/* \
    && wget -P ~ https://github.com/cyrus-and/gdb-dashboard/raw/master/.gdbinit

WORKDIR /repo