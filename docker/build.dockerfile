ARG DEBIAN_RELEASE=forky
FROM turnertech/nmbs-builder:${DEBIAN_RELEASE} AS nmbs-build

RUN useradd -ms /bin/bash nmbs
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
