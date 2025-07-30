# AQUA V. Quantum Navigation System - CI/CD Docker Build Environment
# Document: QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-CYB-812-00-02-TPL-CI-002-QDAT-v1.0.0.dockerfile
# Owner: QDAT (Data Governance Division)
# Site: Silicon Valley (25SVD)
# =============================================================================
# Copyright (C) 2025 GAIA AIR - ROBBBO-T
# Aerospace and Quantum United Advanced Venture (AQUA V.)
# =============================================================================
# Multi-stage Dockerfile for QNS TRL 6 CI/CD Pipeline
# =============================================================================

# Stage 1: Base dependencies
# SECURITY: Pinned to specific digest for reproducible builds
FROM ubuntu:22.04@sha256:9a0bdde4188b896a372804be2384015e90e3f84906b750c1a53539b585fbbe7f AS base-deps

LABEL maintainer="qns-dev@aqua-v.aerospace"
LABEL version="1.0.0"
LABEL description="AQUA V. QNS CI/CD Build Environment - Base Dependencies"
LABEL trl="6"
LABEL site="25SVD"

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Update and install base system packages
RUN apt-get update -qq && \
    apt-get install -y --no-install-recommends \
        # Build essentials
        build-essential \
        gcc-11 \
        g++-11 \
        gdb \
        # Build tools
        cmake \
        ninja-build \
        ccache \
        pkg-config \
        # Version control
        git \
        git-lfs \
        # Network tools
        curl \
        wget \
        ca-certificates \
        gnupg \
        lsb-release \
        # Python for tooling
        python3 \
        python3-pip \
        python3-dev \
        python3-venv \
        # System utilities
        sudo \
        locales \
        tzdata \
        unzip \
        xz-utils \
    && rm -rf /var/lib/apt/lists/*

# Set default compiler versions
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 100

# Generate locale
RUN locale-gen en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

# =============================================================================
# Stage 2: Development dependencies
FROM base-deps AS dev-deps

LABEL description="AQUA V. QNS CI/CD Build Environment - Development Dependencies"

# Install development libraries
RUN apt-get update -qq && \
    apt-get install -y --no-install-recommends \
        # Math libraries
        libeigen3-dev \
        liblapack-dev \
        libblas-dev \
        libopenblas-dev \
        # Parallel computing
        libomp-dev \
        libopenmpi-dev \
        # Qt6 for GUI components
        qt6-base-dev \
        qt6-tools-dev \
        libqt6core6 \
        libqt6widgets6 \
        libqt6network6 \
        libqt6concurrent6 \
        libqt6serialport6-dev \
        # Boost libraries
        libboost-all-dev \
        # Security libraries
        libssl-dev \
        libsodium-dev \
        # Serialization
        libprotobuf-dev \
        protobuf-compiler \
        nlohmann-json3-dev \
        # Testing frameworks
        libgtest-dev \
        libgmock-dev \
        libbenchmark-dev \
        # Code quality tools
        clang-format-14 \
        clang-tidy-14 \
        cppcheck \
        iwyu \
        # Coverage tools
        lcov \
        gcovr \
        # Documentation
        doxygen \
        graphviz \
        # Performance analysis
        valgrind \
        linux-tools-generic \
    && rm -rf /var/lib/apt/lists/*

# Build and install Google Test from source (for latest features)
RUN cd /usr/src/googletest && \
    cmake -B build -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        -DBUILD_SHARED_LIBS=ON && \
    cmake --build build --parallel && \
    cmake --install build && \
    ldconfig

# =============================================================================
# Stage 3: Quantum SDK and tools
FROM dev-deps AS quantum-deps

LABEL description="AQUA V. QNS CI/CD Build Environment - Quantum Dependencies"

# Install quantum simulation dependencies
RUN apt-get update -qq && \
    apt-get install -y --no-install-recommends \
        # Scientific Python packages
        python3-numpy \
        python3-scipy \
        python3-matplotlib \
        python3-pandas \
        # Additional libraries for quantum computing
        libfftw3-dev \
        libhdf5-dev \
        libnetcdf-dev \
    && rm -rf /var/lib/apt/lists/*

# Install Python quantum packages
RUN pip3 install --no-cache-dir \
        qiskit==0.45.0 \
        qiskit-aer==0.13.0 \
        cirq==1.3.0 \
        pennylane==0.33.0 \
        projectq==0.8.0 \
        numpy==1.24.3 \
        scipy==1.10.1 \
        matplotlib==3.7.2 \
        jupyter==1.0.0 \
        pytest==7.4.3 \
        pytest-cov==4.1.0 \
        black==23.11.0 \
        pylint==3.0.2 \
        mypy==1.7.0

# Create directory for AQUA V. Quantum SDK
RUN mkdir -p /opt/aqua-v/quantum-sdk/{bin,lib,include,share}

# Placeholder for actual Quantum SDK installation
# In production, this would be replaced with actual SDK installation
COPY --chown=root:root quantum_sdk_placeholder.txt /opt/aqua-v/quantum-sdk/README.txt

# =============================================================================
# Stage 4: CI/CD tools
FROM quantum-deps AS ci-tools

LABEL description="AQUA V. QNS CI/CD Build Environment - CI/CD Tools"

# Install CI/CD specific tools
RUN apt-get update -qq && \
    apt-get install -y --no-install-recommends \
        # Container tools
        docker.io \
        docker-compose \
        # Deployment tools
        ansible \
        terraform \
        # Security scanning
        trivy \
        # Database clients (for test data)
        postgresql-client \
        redis-tools \
        # Monitoring tools
        htop \
        iotop \
        sysstat \
    && rm -rf /var/lib/apt/lists/*

# Install GitLab Runner helper
RUN curl -L --output /usr/local/bin/gitlab-runner \
        "https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-linux-amd64" && \
    chmod +x /usr/local/bin/gitlab-runner

# Install additional CI/CD Python tools
RUN pip3 install --no-cache-dir \
        ansible-lint==6.22.0 \
        safety==3.0.0 \
        bandit==1.7.5 \
        pre-commit==3.5.0 \
        commitizen==3.12.0 \
        python-gitlab==4.1.1

# =============================================================================
# Stage 5: Final CI/CD image
FROM ci-tools AS final

LABEL description="AQUA V. QNS CI/CD Build Environment - Final"
LABEL org.opencontainers.image.source="https://gitlab.aqua-v.aerospace/quantum/qns"
LABEL org.opencontainers.image.documentation="https://docs.aqua-v.aerospace/qns/ci"
LABEL org.opencontainers.image.vendor="GAIA AIR - ROBBBO-T"
LABEL org.opencontainers.image.licenses="Proprietary"

# Create build user with sudo privileges
RUN useradd -m -s /bin/bash -u 1000 qns-builder && \
    usermod -aG sudo qns-builder && \
    echo "qns-builder ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Setup build directories
RUN mkdir -p /workspace /cache /artifacts && \
    chown -R qns-builder:qns-builder /workspace /cache /artifacts

# Configure ccache
ENV CCACHE_DIR=/cache/ccache
ENV CCACHE_MAXSIZE=5G
ENV CCACHE_COMPRESS=1
ENV CCACHE_COMPRESSLEVEL=6
ENV CCACHE_HARDLINK=1

# Setup AQUA V. environment variables
ENV AQUA_V_ROOT=/opt/aqua-v
ENV QUANTUM_SDK_ROOT=/opt/aqua-v/quantum-sdk
ENV PATH="${QUANTUM_SDK_ROOT}/bin:/usr/lib/ccache:${PATH}"
ENV LD_LIBRARY_PATH="${QUANTUM_SDK_ROOT}/lib:${LD_LIBRARY_PATH}"
ENV CMAKE_PREFIX_PATH="${QUANTUM_SDK_ROOT}:${CMAKE_PREFIX_PATH}"

# QNS specific environment
ENV QNS_TRL=6
ENV QNS_SITE_CODE=25SVD
ENV QNS_UPDATE_RATE_HZ=1000
ENV QNS_GRAVITOMETER_SENSITIVITY=1e-12
ENV QNS_MAGNETOMETER_RANGE=1e-9

# Copy CI/CD scripts
COPY --chown=qns-builder:qns-builder ci-scripts/ /opt/aqua-v/ci-scripts/
RUN chmod +x /opt/aqua-v/ci-scripts/*.sh

# Create entrypoint script
RUN echo '#!/bin/bash\n\
set -e\n\
\n\
# Initialize ccache if needed\n\
if [ ! -d "$CCACHE_DIR" ]; then\n\
    mkdir -p "$CCACHE_DIR"\n\
fi\n\
\n\
# Print environment info\n\
echo "================================================"\n\
echo "AQUA V. QNS CI/CD Environment v1.0.0"\n\
echo "TRL: ${QNS_TRL} - Flight Testing"\n\
echo "Site: ${QNS_SITE_CODE} - Silicon Valley"\n\
echo "================================================"\n\
echo "GCC Version: $(gcc --version | head -n1)"\n\
echo "CMake Version: $(cmake --version | head -n1)"\n\
echo "Python Version: $(python3 --version)"\n\
echo "================================================"\n\
\n\
# Execute command\n\
exec "$@"' > /entrypoint.sh && chmod +x /entrypoint.sh

# Switch to build user
USER qns-builder
WORKDIR /workspace

# Set entrypoint
ENTRYPOINT ["/entrypoint.sh"]
CMD ["/bin/bash"]

# Health check
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
    CMD gcc --version && cmake --version && python3 --version || exit 1

# =============================================================================
# Build metadata
ARG BUILD_DATE
ARG BUILD_VERSION
ARG VCS_REF

LABEL org.opencontainers.image.created="${BUILD_DATE}"
LABEL org.opencontainers.image.version="${BUILD_VERSION}"
LABEL org.opencontainers.image.revision="${VCS_REF}"
LABEL aqua-v.qns.trl="6"
LABEL aqua-v.qns.status="flight-testing"
LABEL aqua-v.qns.update-rate="1000Hz"

# EOF
