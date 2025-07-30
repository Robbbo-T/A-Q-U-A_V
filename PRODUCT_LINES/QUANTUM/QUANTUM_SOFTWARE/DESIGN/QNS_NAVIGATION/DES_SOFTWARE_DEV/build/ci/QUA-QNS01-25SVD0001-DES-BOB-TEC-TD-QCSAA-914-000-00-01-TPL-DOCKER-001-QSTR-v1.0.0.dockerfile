# AQUA V. QNS Docker Build Environment
FROM ubuntu:22.04

LABEL maintainer="qns-dev@aqua-v.aerospace"
LABEL version="1.0.0"
LABEL description="AQUA V. Quantum Navigation System Build Environment"

# Prevent interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install base dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    ninja-build \
    ccache \
    pkg-config \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Install development dependencies
RUN apt-get update && apt-get install -y \
    libeigen3-dev \
    qt6-base-dev \
    qt6-tools-dev \
    libgtest-dev \
    libboost-all-dev \
    libssl-dev \
    libprotobuf-dev \
    protobuf-compiler \
    && rm -rf /var/lib/apt/lists/*

# Install quantum simulation tools
RUN pip3 install qiskit numpy scipy matplotlib

# Create build user
RUN useradd -m -s /bin/bash qns-builder
USER qns-builder
WORKDIR /home/qns-builder

# Set environment
ENV CC=/usr/bin/gcc
ENV CXX=/usr/bin/g++
ENV PATH="/usr/lib/ccache:${PATH}"

# Entry point
ENTRYPOINT ["/bin/bash"]
