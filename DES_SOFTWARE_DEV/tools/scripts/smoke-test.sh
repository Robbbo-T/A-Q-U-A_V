#!/bin/bash
# Smoke Test Script for AQUA V. Quantum Software
# Document: QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-DTCEC-310-04-01-TPL-SCR-001-QHPC-v1.0.0.sh
# Version: 1.0.0
# Owner: QHPC (Quantum High Performance Computing Division)

set -euo pipefail

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Logging functions
log() {
    echo -e "${BLUE}[$(date +'%Y-%m-%d %H:%M:%S')]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1" >&2
}

success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

usage() {
    cat << EOF
Usage: $0 <environment>

Environments:
  dev        Development environment
  staging    Staging environment
  production Production environment

Description:
  Runs smoke tests against the deployed AQUA V. Quantum Software
  to verify basic functionality and quantum service availability.

Examples:
  $0 staging
  $0 production

AQUA V. Smoke Test Suite v1.0.0
Part of €40B aerospace quantum computing initiative
EOF
}

# Environment configurations
setup_environment() {
    local env=$1
    
    case ${env} in
        dev)
            export BASE_URL="https://dev-quantum.aqua-v.internal"
            export API_KEY="dev-api-key"
            export TIMEOUT=30
            ;;
        staging)
            export BASE_URL="https://staging-quantum.aqua-v.internal"
            export API_KEY="staging-api-key"
            export TIMEOUT=60
            ;;
        production)
            export BASE_URL="https://quantum.aqua-v.aerospace"
            export API_KEY="prod-api-key"
            export TIMEOUT=120
            ;;
        *)
            error "Unknown environment: ${env}"
            usage
            exit 1
            ;;
    esac
    
    log "Testing environment: ${env}"
    log "Base URL: ${BASE_URL}"
    log "Timeout: ${TIMEOUT}s"
}

# Test health endpoint
test_health_endpoint() {
    log "Testing health endpoint..."
    
    local health_url="${BASE_URL}/health"
    local response=$(curl -s -k --max-time ${TIMEOUT} --write-out "HTTPSTATUS:%{http_code}" "${health_url}" || echo "HTTPSTATUS:000")
    local body=$(echo "${response}" | sed -E 's/HTTPSTATUS\:[0-9]{3}$//')
    local status=$(echo "${response}" | tr -d '\n' | sed -E 's/.*HTTPSTATUS:([0-9]{3})$/\1/')
    
    if [[ "${status}" == "200" ]]; then
        success "Health endpoint responsive"
        log "Response: ${body}"
        return 0
    else
        error "Health endpoint failed (HTTP ${status})"
        return 1
    fi
}

# Test API endpoints
test_api_endpoints() {
    log "Testing API endpoints..."
    
    local api_url="${BASE_URL}/api/v1"
    local tests_passed=0
    local tests_total=0
    
    # Test 1: API Status
    ((tests_total++))
    log "Testing API status..."
    local response=$(curl -s -k --max-time ${TIMEOUT} --write-out "HTTPSTATUS:%{http_code}" "${api_url}/status" || echo "HTTPSTATUS:000")
    local status=$(echo "${response}" | tr -d '\n' | sed -E 's/.*HTTPSTATUS:([0-9]{3})$/\1/')
    
    if [[ "${status}" == "200" ]]; then
        success "API status endpoint responsive"
        ((tests_passed++))
    else
        error "API status endpoint failed (HTTP ${status})"
    fi
    
    # Test 2: Quantum Service Discovery
    ((tests_total++))
    log "Testing quantum service discovery..."
    local quantum_url="${api_url}/quantum/services"
    response=$(curl -s -k --max-time ${TIMEOUT} --write-out "HTTPSTATUS:%{http_code}" "${quantum_url}" || echo "HTTPSTATUS:000")
    status=$(echo "${response}" | tr -d '\n' | sed -E 's/.*HTTPSTATUS:([0-9]{3})$/\1/')
    
    if [[ "${status}" == "200" ]]; then
        success "Quantum service discovery responsive"
        ((tests_passed++))
    else
        warning "Quantum service discovery not available (HTTP ${status})"
    fi
    
    # Test 3: Authentication test (if API key provided)
    if [[ -n "${API_KEY}" ]] && [[ "${API_KEY}" != "dev-api-key" ]]; then
        ((tests_total++))
        log "Testing authentication..."
        response=$(curl -s -k --max-time ${TIMEOUT} -H "X-API-Key: ${API_KEY}" --write-out "HTTPSTATUS:%{http_code}" "${api_url}/auth/test" || echo "HTTPSTATUS:000")
        status=$(echo "${response}" | tr -d '\n' | sed -E 's/.*HTTPSTATUS:([0-9]{3})$/\1/')
        
        if [[ "${status}" == "200" ]]; then
            success "Authentication test passed"
            ((tests_passed++))
        else
            warning "Authentication test failed (HTTP ${status})"
        fi
    fi
    
    log "API tests: ${tests_passed}/${tests_total} passed"
    return $(( tests_total - tests_passed ))
}

# Test quantum-specific endpoints
test_quantum_endpoints() {
    log "Testing quantum-specific endpoints..."
    
    local quantum_base="${BASE_URL}/api/v1/quantum"
    local tests_passed=0
    local tests_total=0
    
    # Test 1: Quantum simulator status
    ((tests_total++))
    log "Testing quantum simulator status..."
    local response=$(curl -s -k --max-time ${TIMEOUT} --write-out "HTTPSTATUS:%{http_code}" "${quantum_base}/simulator/status" || echo "HTTPSTATUS:000")
    local status=$(echo "${response}" | tr -d '\n' | sed -E 's/.*HTTPSTATUS:([0-9]{3})$/\1/')
    
    if [[ "${status}" == "200" ]]; then
        success "Quantum simulator status responsive"
        ((tests_passed++))
    else
        warning "Quantum simulator status not available (HTTP ${status})"
    fi
    
    # Test 2: Circuit validation endpoint
    ((tests_total++))
    log "Testing circuit validation..."
    local circuit_data='{"qubits": 2, "gates": [{"type": "H", "qubit": 0}, {"type": "CNOT", "control": 0, "target": 1}]}'
    response=$(curl -s -k --max-time ${TIMEOUT} -H "Content-Type: application/json" -d "${circuit_data}" --write-out "HTTPSTATUS:%{http_code}" "${quantum_base}/circuit/validate" || echo "HTTPSTATUS:000")
    status=$(echo "${response}" | tr -d '\n' | sed -E 's/.*HTTPSTATUS:([0-9]{3})$/\1/')
    
    if [[ "${status}" == "200" ]]; then
        success "Circuit validation responsive"
        ((tests_passed++))
    else
        warning "Circuit validation not available (HTTP ${status})"
    fi
    
    # Test 3: Algorithm library
    ((tests_total++))
    log "Testing algorithm library..."
    response=$(curl -s -k --max-time ${TIMEOUT} --write-out "HTTPSTATUS:%{http_code}" "${quantum_base}/algorithms" || echo "HTTPSTATUS:000")
    status=$(echo "${response}" | tr -d '\n' | sed -E 's/.*HTTPSTATUS:([0-9]{3})$/\1/')
    
    if [[ "${status}" == "200" ]]; then
        success "Algorithm library responsive"
        ((tests_passed++))
    else
        warning "Algorithm library not available (HTTP ${status})"
    fi
    
    log "Quantum tests: ${tests_passed}/${tests_total} passed"
    return $(( tests_total - tests_passed ))
}

# Test performance endpoints
test_performance() {
    log "Testing performance characteristics..."
    
    local start_time=$(date +%s%N)
    local response=$(curl -s -k --max-time 5 "${BASE_URL}/health" || echo "TIMEOUT")
    local end_time=$(date +%s%N)
    
    if [[ "${response}" == "TIMEOUT" ]]; then
        warning "Performance test timed out"
        return 1
    fi
    
    local duration_ms=$(( (end_time - start_time) / 1000000 ))
    log "Response time: ${duration_ms}ms"
    
    if (( duration_ms < 1000 )); then
        success "Response time within acceptable limits"
        return 0
    else
        warning "Response time higher than expected: ${duration_ms}ms"
        return 1
    fi
}

# Test database connectivity (if endpoint exists)
test_database_connectivity() {
    log "Testing database connectivity..."
    
    local db_url="${BASE_URL}/api/v1/system/database/health"
    local response=$(curl -s -k --max-time ${TIMEOUT} --write-out "HTTPSTATUS:%{http_code}" "${db_url}" || echo "HTTPSTATUS:000")
    local status=$(echo "${response}" | tr -d '\n' | sed -E 's/.*HTTPSTATUS:([0-9]{3})$/\1/')
    
    if [[ "${status}" == "200" ]]; then
        success "Database connectivity test passed"
        return 0
    else
        warning "Database connectivity test not available or failed (HTTP ${status})"
        return 1
    fi
}

# Test metrics endpoint
test_metrics() {
    log "Testing metrics endpoint..."
    
    local metrics_url="${BASE_URL}/metrics"
    local response=$(curl -s -k --max-time ${TIMEOUT} --write-out "HTTPSTATUS:%{http_code}" "${metrics_url}" || echo "HTTPSTATUS:000")
    local status=$(echo "${response}" | tr -d '\n' | sed -E 's/.*HTTPSTATUS:([0-9]{3})$/\1/')
    
    if [[ "${status}" == "200" ]]; then
        success "Metrics endpoint responsive"
        return 0
    else
        warning "Metrics endpoint not available (HTTP ${status})"
        return 1
    fi
}

# Main smoke test function
run_smoke_tests() {
    local environment=$1
    
    log "AQUA V. Quantum Software Smoke Tests"
    log "===================================="
    log "Environment: ${environment}"
    log "Timestamp: $(date)"
    log ""
    
    setup_environment "${environment}"
    
    local total_tests=0
    local passed_tests=0
    
    # Core functionality tests
    log "=== Core Functionality Tests ==="
    ((total_tests++))
    if test_health_endpoint; then
        ((passed_tests++))
    fi
    
    ((total_tests++))
    if test_api_endpoints; then
        ((passed_tests++))
    fi
    
    ((total_tests++))
    if test_performance; then
        ((passed_tests++))
    fi
    
    # Quantum-specific tests
    log ""
    log "=== Quantum Service Tests ==="
    ((total_tests++))
    if test_quantum_endpoints; then
        ((passed_tests++))
    fi
    
    # Optional tests (don't count toward failure)
    log ""
    log "=== Optional Service Tests ==="
    test_database_connectivity || true
    test_metrics || true
    
    # Summary
    log ""
    log "=== Test Summary ==="
    log "Total Critical Tests: ${total_tests}"
    log "Passed: ${passed_tests}"
    log "Failed: $((total_tests - passed_tests))"
    
    if (( passed_tests == total_tests )); then
        success "All critical smoke tests passed!"
        log "AQUA V. Quantum Software is functioning correctly on ${environment}"
        return 0
    else
        error "Some critical smoke tests failed"
        log "Failed tests: $((total_tests - passed_tests))/${total_tests}"
        return 1
    fi
}

# Parse command line arguments
if [[ $# -eq 0 ]]; then
    usage
    exit 1
fi

ENVIRONMENT=""

while [[ $# -gt 0 ]]; do
    case $1 in
        --help)
            usage
            exit 0
            ;;
        *)
            if [[ -z "${ENVIRONMENT}" ]]; then
                ENVIRONMENT="$1"
            else
                error "Unknown argument: $1"
                usage
                exit 1
            fi
            shift
            ;;
    esac
done

# Validate arguments
if [[ -z "${ENVIRONMENT}" ]]; then
    error "Environment is required"
    usage
    exit 1
fi

# Execute smoke tests
run_smoke_tests "${ENVIRONMENT}"