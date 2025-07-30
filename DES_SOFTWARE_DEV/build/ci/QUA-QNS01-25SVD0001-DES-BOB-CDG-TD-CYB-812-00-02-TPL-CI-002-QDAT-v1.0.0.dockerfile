# Quantum Software Development CI/CD Environment
# Version: 1.0.0
# ATA-Chapter: CYB-812 (Cybersecurity & DevOps)

FROM ubuntu:22.04

LABEL maintainer="quantum-dev@example.com"
LABEL version="1.0.0"
LABEL description="CI/CD environment for Quantum Software Development"

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Install base dependencies
RUN apt-get update && apt-get install -y \
    # Build essentials
    build-essential \
    cmake \
    ninja-build \
    ccache \
    # Version control
    git \
    git-lfs \
    # Compilers and tools
    gcc-12 \
    g++-12 \
    clang-15 \
    clang-tidy-15 \
    clang-format-15 \
    # Static analysis tools
    cppcheck \
    valgrind \
    # Code coverage
    lcov \
    gcovr \
    # Documentation tools
    doxygen \
    graphviz \
    plantuml \
    # Python for scripts
    python3 \
    python3-pip \
    python3-venv \
    # Debugging tools
    gdb \
    strace \
    # Performance analysis
    linux-tools-generic \
    linux-tools-common \
    # Network tools
    curl \
    wget \
    # Compression tools
    zip \
    unzip \
    tar \
    # Other utilities
    jq \
    make \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Set default compiler versions
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 100 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-15 100 \
    && update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-15 100 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-15 100

# Install CMake (specific version for consistency)
ARG CMAKE_VERSION=3.28.0
RUN wget -q https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh \
    && chmod +x cmake-${CMAKE_VERSION}-Linux-x86_64.sh \
    && ./cmake-${CMAKE_VERSION}-Linux-x86_64.sh --skip-license --prefix=/usr/local \
    && rm cmake-${CMAKE_VERSION}-Linux-x86_64.sh

# Install Python packages
RUN pip3 install --no-cache-dir \
    pytest==7.4.3 \
    pytest-cov==4.1.0 \
    pytest-xdist==3.5.0 \
    numpy==1.24.3 \
    scipy==1.11.4 \
    matplotlib==3.7.2 \
    pandas==2.0.3 \
    pyyaml==6.0.1 \
    jsonschema==4.19.2 \
    mkdocs==1.5.3 \
    mkdocs-material==9.4.14 \
    pymdown-extensions==10.5

# Install Quantum SDK (placeholder - replace with actual SDK)
ARG QUANTUM_SDK_VERSION=2.0.0
RUN mkdir -p /opt/quantum-sdk && \
    echo "Quantum SDK ${QUANTUM_SDK_VERSION} placeholder" > /opt/quantum-sdk/version.txt

# Set up environment variables
ENV QUANTUM_SDK_PATH=/opt/quantum-sdk
ENV PATH="${QUANTUM_SDK_PATH}/bin:${PATH}"
ENV LD_LIBRARY_PATH="${QUANTUM_SDK_PATH}/lib:${LD_LIBRARY_PATH}"

# Create non-root user for builds
RUN useradd -m -s /bin/bash builder && \
    mkdir -p /workspace && \
    chown -R builder:builder /workspace

# Set up ccache
RUN mkdir -p /ccache && \
    chown -R builder:builder /ccache
ENV CCACHE_DIR=/ccache
ENV CCACHE_MAXSIZE=5G

# Switch to non-root user
USER builder
WORKDIR /workspace

# Set build environment variables
ENV CC=/usr/bin/gcc
ENV CXX=/usr/bin/g++
ENV CMAKE_GENERATOR="Ninja"
ENV CTEST_OUTPUT_ON_FAILURE=1

# Entry point
CMD ["/bin/bash"]
