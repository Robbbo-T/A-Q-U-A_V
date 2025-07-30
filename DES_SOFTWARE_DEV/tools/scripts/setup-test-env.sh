#!/bin/bash
# Test Environment Setup Script
# Sets up the environment for different test types

set -euo pipefail

TEST_TYPE="${1:-unit}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

echo "Setting up test environment for: ${TEST_TYPE} tests"

case ${TEST_TYPE} in
    unit)
        echo "Configuring unit test environment..."
        export QUANTUM_TEST_MODE="unit"
        export QUANTUM_SIMULATOR="mock"
        ;;
    integration)
        echo "Configuring integration test environment..."
        export QUANTUM_TEST_MODE="integration"
        export QUANTUM_SIMULATOR="qiskit"
        # Start test containers if needed
        if command -v docker-compose &> /dev/null; then
            docker-compose -f "${PROJECT_ROOT}/tests/docker-compose.test.yml" up -d
        fi
        ;;
    performance)
        echo "Configuring performance test environment..."
        export QUANTUM_TEST_MODE="performance"
        export QUANTUM_SIMULATOR="high_performance"
        # Set performance testing flags
        export ENABLE_PROFILING=1
        export COLLECT_METRICS=1
        ;;
    *)
        echo "Unknown test type: ${TEST_TYPE}"
        exit 1
        ;;
esac

echo "Test environment ready"
