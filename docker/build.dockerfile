ARG DEBIAN_RELEASE=forky
FROM debian:${DEBIAN_RELEASE} AS nmbs-build

RUN apt-get update && apt-get install --no-install-recommends --yes \
    build-essential cmake debhelper help2man libgtest-dev doxygen libargparse-dev libexiv2-dev libxml2-dev pkg-config libglib2.0-dev libnautilus-extension-dev ninja-build xml-core && \
    useradd -ms /bin/bash nmbs

USER nmbs
WORKDIR /home/nmbs/src/nmbs
COPY --chown=nmbs:nmbs . .

RUN cmake --preset debug &&  \
    cmake --build --preset debug && \
    cmake --preset release && \
    cmake --build --preset release && \
    cpack -B build
