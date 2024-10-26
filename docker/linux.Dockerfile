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

# (ref.) [Running Docker Containers as Current Host User](https://jtreminio.com/blog/running-docker-containers-as-current-host-user/#ok-so-what-actually-works)
RUN groupadd -g $GROUP_ID app \
    && useradd --system -u $USER_ID -g app --create-home --no-log-init app \
    && mkdir -p /repo /app /out \
    && chown -R app /repo /app /out
USER app

RUN wget -P ~ https://github.com/cyrus-and/gdb-dashboard/raw/master/.gdbinit \
    && python3.12 -m venv /app/.venv \
    && /app/.venv/bin/pip install --no-cache-dir graphviz

WORKDIR /repo
ENTRYPOINT ["just"]