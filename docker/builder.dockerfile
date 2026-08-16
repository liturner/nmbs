ARG DEBIAN_RELEASE=trixie
FROM debian:${DEBIAN_RELEASE}

# Note, we dont use the prepare script here as it would be sub-optimal for docker layering. Slight divergence may occur,
# if so just correct it manually. This wont change that often!
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
