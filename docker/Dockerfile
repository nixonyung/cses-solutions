FROM debian:sid-slim

ARG USER_ID
ARG GROUP_ID

RUN --mount=type=cache,target=/root/.cache/pip \
    apt-get update \
    && apt-get install -y --no-install-recommends \
        g++-14 gdb valgrind \
        python3.12 python3.12-venv graphviz \
        wget ca-certificates \
        just parallel time \
    && rm -rf /var/lib/apt/lists/*

RUN wget -P ~ https://github.com/cyrus-and/gdb-dashboard/raw/master/.gdbinit \
    && python3.12 -m venv /app/.venv \
    && /app/.venv/bin/pip install --no-cache-dir graphviz

WORKDIR /repo
ENTRYPOINT ["just"]