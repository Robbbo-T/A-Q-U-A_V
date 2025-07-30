#!/bin/bash
# Deployment Verification Script for AQUA V. Quantum Software
# Document: QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-DTCEC-310-05-01-TPL-SCR-001-QHPC-v1.0.0.sh
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
  Verifies deployment of AQUA V. Quantum Software by running comprehensive
  validation checks including service health, quantum functionality, and
  performance benchmarks.

Examples:
  $0 staging
  $0 production

AQUA V. Deployment Verification v1.0.0
Part of €40B aerospace quantum computing initiative
EOF
}

# Environment configurations
setup_environment() {
    local env=$1
    
    case ${env} in
        dev)
            export BASE_URL="https://dev-quantum.aqua-v.internal"
            export SSH_HOST="dev-quantum.aqua-v.internal"
            export DEPLOYMENT_USER="aqua-deploy"
            export DEPLOY_PATH="/opt/aqua-v/quantum-dev"
            export SERVICE_NAME="aqua-v-quantum-dev"
            export EXPECTED_VERSION_FILE="${DEPLOY_PATH}/VERSION"
            ;;
        staging)
            export BASE_URL="https://staging-quantum.aqua-v.internal"
            export SSH_HOST="staging-quantum.aqua-v.internal"
            export DEPLOYMENT_USER="aqua-deploy"
            export DEPLOY_PATH="/opt/aqua-v/quantum-staging"
            export SERVICE_NAME="aqua-v-quantum-staging"
            export EXPECTED_VERSION_FILE="${DEPLOY_PATH}/VERSION"
            ;;
        production)
            export BASE_URL="https://quantum.aqua-v.aerospace"
            export SSH_HOST="prod-quantum.aqua-v.aerospace"
            export DEPLOYMENT_USER="aqua-deploy"
            export DEPLOY_PATH="/opt/aqua-v/quantum-prod"
            export SERVICE_NAME="aqua-v-quantum-prod"
            export EXPECTED_VERSION_FILE="${DEPLOY_PATH}/VERSION"
            ;;
        *)
            error "Unknown environment: ${env}"
            usage
            exit 1
            ;;
    esac
    
    log "Verifying deployment on environment: ${env}"
    log "Base URL: ${BASE_URL}"
    log "SSH Host: ${SSH_HOST}"
    log "Deploy Path: ${DEPLOY_PATH}"
}

# Verify service status
verify_service_status() {
    log "Verifying service status..."
    
    local service_status=$(ssh ${DEPLOYMENT_USER}@${SSH_HOST} "sudo systemctl is-active ${SERVICE_NAME}" 2>/dev/null || echo "unknown")
    local service_enabled=$(ssh ${DEPLOYMENT_USER}@${SSH_HOST} "sudo systemctl is-enabled ${SERVICE_NAME}" 2>/dev/null || echo "unknown")
    
    if [[ "${service_status}" == "active" ]]; then
        success "Service ${SERVICE_NAME} is active"
    else
        error "Service ${SERVICE_NAME} is not active (status: ${service_status})"
        return 1
    fi
    
    if [[ "${service_enabled}" == "enabled" ]]; then
        success "Service ${SERVICE_NAME} is enabled for auto-start"
    else
        warning "Service ${SERVICE_NAME} is not enabled for auto-start (status: ${service_enabled})"
    fi
    
    return 0
}

# Verify deployment version
verify_deployment_version() {
    log "Verifying deployment version..."
    
    local deployed_version=$(ssh ${DEPLOYMENT_USER}@${SSH_HOST} "cat ${EXPECTED_VERSION_FILE} 2>/dev/null || echo 'unknown'")
    
    if [[ "${deployed_version}" == "unknown" ]]; then
        error "Could not determine deployed version"
        return 1
    fi
    
    success "Deployed version: ${deployed_version}"
    
    # Verify version via API
    local api_version=$(curl -s -k --max-time 30 "${BASE_URL}/api/v1/version" | jq -r '.version' 2>/dev/null || echo "unknown")
    
    if [[ "${api_version}" == "${deployed_version}" ]]; then
        success "API version matches deployment version"
    else
        warning "API version (${api_version}) differs from deployment version (${deployed_version})"
    fi
    
    return 0
}

# Verify file permissions and ownership
verify_file_permissions() {
    log "Verifying file permissions..."
    
    ssh ${DEPLOYMENT_USER}@${SSH_HOST} "
        # Check main executable permissions
        if [[ -x ${DEPLOY_PATH}/bin/aqua_v_qns ]]; then
            echo 'Main executable is executable'
        else
            echo 'ERROR: Main executable is not executable'
            exit 1
        fi
        
        # Check ownership
        if [[ \$(stat -c '%U' ${DEPLOY_PATH}) == '${DEPLOYMENT_USER}' ]]; then
            echo 'Deployment ownership is correct'
        else
            echo 'WARNING: Deployment ownership may be incorrect'
        fi
        
        # Check configuration files
        if [[ -r ${DEPLOY_PATH}/config/quantum-config.json ]]; then
            echo 'Configuration files are readable'
        else
            echo 'WARNING: Configuration files may not be accessible'
        fi
    "
    
    success "File permissions verified"
    return 0
}

# Verify quantum service endpoints
verify_quantum_endpoints() {
    log "Verifying quantum service endpoints..."
    
    local tests_passed=0
    local tests_total=4
    
    # Test 1: Health endpoint
    log "Testing health endpoint..."
    if curl -f -s -k --max-time 30 "${BASE_URL}/health" > /dev/null; then
        success "Health endpoint responsive"
        ((tests_passed++))
    else
        error "Health endpoint not responsive"
    fi
    
    # Test 2: API status
    log "Testing API status..."
    local api_response=$(curl -s -k --max-time 30 "${BASE_URL}/api/v1/status" | jq -r '.status' 2>/dev/null || echo "error")
    if [[ "${api_response}" == "ok" ]] || [[ "${api_response}" == "healthy" ]]; then
        success "API status endpoint responsive"
        ((tests_passed++))
    else
        error "API status endpoint not responsive"
    fi
    
    # Test 3: Quantum simulator
    log "Testing quantum simulator endpoint..."
    if curl -f -s -k --max-time 30 "${BASE_URL}/api/v1/quantum/simulator/status" > /dev/null; then
        success "Quantum simulator endpoint responsive"
        ((tests_passed++))
    else
        warning "Quantum simulator endpoint not responsive"
    fi
    
    # Test 4: Circuit validation
    log "Testing circuit validation..."
    local test_circuit='{"qubits": 2, "gates": [{"type": "H", "qubit": 0}]}'
    if curl -f -s -k --max-time 30 -H "Content-Type: application/json" -d "${test_circuit}" "${BASE_URL}/api/v1/quantum/circuit/validate" > /dev/null; then
        success "Circuit validation endpoint responsive"
        ((tests_passed++))
    else
        warning "Circuit validation endpoint not responsive"
    fi
    
    log "Quantum endpoint verification: ${tests_passed}/${tests_total} passed"
    
    if (( tests_passed >= 2 )); then
        return 0
    else
        return 1
    fi
}

# Verify configuration integrity
verify_configuration() {
    log "Verifying configuration integrity..."
    
    ssh ${DEPLOYMENT_USER}@${SSH_HOST} "
        cd ${DEPLOY_PATH}
        
        # Check if configuration files exist
        config_files=('config/quantum-config.json' 'config/service.conf')
        for config_file in \"\${config_files[@]}\"; do
            if [[ -f \"\${config_file}\" ]]; then
                echo \"Configuration file exists: \${config_file}\"
                
                # Validate JSON files
                if [[ \"\${config_file}\" == *.json ]]; then
                    if python3 -m json.tool \"\${config_file}\" > /dev/null 2>&1; then
                        echo \"JSON configuration is valid: \${config_file}\"
                    else
                        echo \"ERROR: Invalid JSON configuration: \${config_file}\"
                        exit 1
                    fi
                fi
            else
                echo \"WARNING: Configuration file missing: \${config_file}\"
            fi
        done
        
        # Check if required directories exist
        required_dirs=('bin' 'lib' 'config')
        for dir in \"\${required_dirs[@]}\"; do
            if [[ -d \"\${dir}\" ]]; then
                echo \"Required directory exists: \${dir}\"
            else
                echo \"ERROR: Required directory missing: \${dir}\"
                exit 1
            fi
        done
    "
    
    success "Configuration integrity verified"
    return 0
}

# Verify performance benchmarks
verify_performance() {
    log "Verifying performance benchmarks..."
    
    # Response time test
    local start_time=$(date +%s%N)
    local health_response=$(curl -s -k --max-time 10 "${BASE_URL}/health" || echo "TIMEOUT")
    local end_time=$(date +%s%N)
    
    if [[ "${health_response}" == "TIMEOUT" ]]; then
        warning "Health endpoint response timed out"
        return 1
    fi
    
    local response_time_ms=$(( (end_time - start_time) / 1000000 ))
    log "Health endpoint response time: ${response_time_ms}ms"
    
    if (( response_time_ms < 2000 )); then
        success "Response time within acceptable limits"
    else
        warning "Response time higher than expected: ${response_time_ms}ms"
    fi
    
    # Memory usage check
    local memory_usage=$(ssh ${DEPLOYMENT_USER}@${SSH_HOST} "ps -o pid,ppid,rss,cmd -p \$(pgrep -f '${SERVICE_NAME}' | head -1) 2>/dev/null | tail -1 | awk '{print \$3}'" || echo "0")
    local memory_mb=$((memory_usage / 1024))
    
    log "Service memory usage: ${memory_mb}MB"
    
    if (( memory_mb < 2048 )); then
        success "Memory usage within acceptable limits"
    else
        warning "Memory usage higher than expected: ${memory_mb}MB"
    fi
    
    return 0
}

# Verify logs for errors
verify_logs() {
    log "Verifying service logs..."
    
    # Check for recent errors in service logs
    local error_count=$(ssh ${DEPLOYMENT_USER}@${SSH_HOST} "sudo journalctl -u ${SERVICE_NAME} --since '10 minutes ago' --no-pager | grep -i error | wc -l" || echo "0")
    
    if (( error_count == 0 )); then
        success "No recent errors found in service logs"
    else
        warning "Found ${error_count} recent errors in service logs"
        
        # Show recent errors
        ssh ${DEPLOYMENT_USER}@${SSH_HOST} "sudo journalctl -u ${SERVICE_NAME} --since '10 minutes ago' --no-pager | grep -i error | tail -5" || true
    fi
    
    # Check application logs if they exist
    local app_log_path="${DEPLOY_PATH}/logs/application.log"
    local app_errors=$(ssh ${DEPLOYMENT_USER}@${SSH_HOST} "tail -100 ${app_log_path} 2>/dev/null | grep -i error | wc -l" || echo "0")
    
    if (( app_errors == 0 )); then
        success "No recent errors found in application logs"
    else
        warning "Found ${app_errors} recent errors in application logs"
    fi
    
    return 0
}

# Main verification function
run_verification() {
    local environment=$1
    
    log "AQUA V. Quantum Software Deployment Verification"
    log "==============================================="
    log "Environment: ${environment}"
    log "Timestamp: $(date)"
    log ""
    
    setup_environment "${environment}"
    
    local total_checks=0
    local passed_checks=0
    
    # Critical verifications
    log "=== Critical Deployment Checks ==="
    
    ((total_checks++))
    if verify_service_status; then
        ((passed_checks++))
    fi
    
    ((total_checks++))
    if verify_deployment_version; then
        ((passed_checks++))
    fi
    
    ((total_checks++))
    if verify_file_permissions; then
        ((passed_checks++))
    fi
    
    ((total_checks++))
    if verify_quantum_endpoints; then
        ((passed_checks++))
    fi
    
    ((total_checks++))
    if verify_configuration; then
        ((passed_checks++))
    fi
    
    # Optional verifications
    log ""
    log "=== Optional Quality Checks ==="
    verify_performance || true
    verify_logs || true
    
    # Summary
    log ""
    log "=== Verification Summary ==="
    log "Total Critical Checks: ${total_checks}"
    log "Passed: ${passed_checks}"
    log "Failed: $((total_checks - passed_checks))"
    
    if (( passed_checks == total_checks )); then
        success "All critical deployment verifications passed!"
        log "AQUA V. Quantum Software deployment is verified and operational on ${environment}"
        return 0
    else
        error "Some critical deployment verifications failed"
        log "Failed checks: $((total_checks - passed_checks))/${total_checks}"
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

# Execute deployment verification
run_verification "${ENVIRONMENT}"