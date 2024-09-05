FROM debian:sid-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
        g++-14 \
        just \
        parallel \
        time \
        && rm -rf /var/lib/apt/lists/*

WORKDIR /src