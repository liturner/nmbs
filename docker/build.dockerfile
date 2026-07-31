ARG DEBIAN_RELEASE=forky
FROM debian:${DEBIAN_RELEASE} AS nmbs-build

RUN apt-get update && apt-get install --no-install-recommends --yes \
    build-essential \
    cmake \
    debhelper \
    doxygen \
    help2man \
    libargparse-dev \
    libexiv2-dev \
    libglib2.0-dev \
    libgtest-dev \
    libnautilus-extension-dev \
    libxml2-dev \
    ninja-build \
    pkg-config \
    xml-core && \
    useradd -ms /bin/bash nmbs

USER nmbs
WORKDIR /home/nmbs/src/nmbs
COPY --chown=nmbs:nmbs . .

RUN cmake --preset debug &&  \
    cmake --build --preset debug && \
    cmake --preset release && \
    cmake --build --preset release && \
    cpack -B build

WORKDIR /home/nmbs/src/nmbs/build/release
RUN ctest

WORKDIR /home/nmbs/src/nmbs/build/debug
RUN ctest

WORKDIR /home/nmbs
