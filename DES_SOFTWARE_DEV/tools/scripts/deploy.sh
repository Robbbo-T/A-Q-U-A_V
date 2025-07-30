#!/bin/bash
# Deployment Script for AQUA V. Quantum Software
# Document: QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-DTCEC-310-03-01-TPL-SCR-001-QHPC-v1.0.0.sh
# Version: 1.0.0
# Owner: QHPC (Quantum High Performance Computing Division)

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

# AQUA V. deployment configuration
DEPLOYMENT_USER="aqua-deploy"
HEALTH_CHECK_TIMEOUT=300
ROLLBACK_TIMEOUT=600

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Logging function
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
Usage: $0 <environment> <version> [options]

Environments:
  dev        Development environment
  staging    Staging environment  
  production Production environment

Options:
  --dry-run      Show what would be deployed without executing
  --force        Force deployment even if health checks fail
  --rollback     Rollback to previous version
  --help         Show this help message

Examples:
  $0 staging v1.2.3
  $0 production v1.2.3 --dry-run
  $0 staging --rollback

AQUA V. Quantum Software Deployment v1.0.0
Part of €40B aerospace quantum computing initiative
EOF
}

# Environment configurations
setup_environment() {
    local env=$1
    
    case ${env} in
        dev)
            export DEPLOY_HOST="dev-quantum.aqua-v.internal"
            export DEPLOY_PORT="22"
            export DEPLOY_PATH="/opt/aqua-v/quantum-dev"
            export SERVICE_NAME="aqua-v-quantum-dev"
            export HEALTH_CHECK_URL="https://dev-quantum.aqua-v.internal/health"
            ;;
        staging)
            export DEPLOY_HOST="staging-quantum.aqua-v.internal"
            export DEPLOY_PORT="22"
            export DEPLOY_PATH="/opt/aqua-v/quantum-staging"
            export SERVICE_NAME="aqua-v-quantum-staging"
            export HEALTH_CHECK_URL="https://staging-quantum.aqua-v.internal/health"
            ;;
        production)
            export DEPLOY_HOST="prod-quantum.aqua-v.aerospace"
            export DEPLOY_PORT="22"
            export DEPLOY_PATH="/opt/aqua-v/quantum-prod"
            export SERVICE_NAME="aqua-v-quantum-prod"
            export HEALTH_CHECK_URL="https://quantum.aqua-v.aerospace/health"
            ;;
        *)
            error "Unknown environment: ${env}"
            usage
            exit 1
            ;;
    esac
    
    log "Environment: ${env}"
    log "Deploy Host: ${DEPLOY_HOST}"
    log "Deploy Path: ${DEPLOY_PATH}"
    log "Service: ${SERVICE_NAME}"
}

# Pre-deployment checks
pre_deployment_checks() {
    local version=$1
    
    log "Running pre-deployment checks..."
    
    # Check if release package exists
    local package_file="${PROJECT_ROOT}/quantum-software-${version}.tar.gz"
    if [[ ! -f "${package_file}" ]]; then
        error "Release package not found: ${package_file}"
        exit 1
    fi
    
    # Check SSH connectivity
    if ! ssh -o ConnectTimeout=10 -p ${DEPLOY_PORT} ${DEPLOYMENT_USER}@${DEPLOY_HOST} "echo 'Connection test successful'" &>/dev/null; then
        error "Cannot connect to deployment host: ${DEPLOY_HOST}:${DEPLOY_PORT}"
        exit 1
    fi
    
    # Check disk space on target
    local available_space=$(ssh -p ${DEPLOY_PORT} ${DEPLOYMENT_USER}@${DEPLOY_HOST} "df ${DEPLOY_PATH} | tail -1 | awk '{print \$4}'")
    local required_space=1048576  # 1GB in KB
    if (( available_space < required_space )); then
        error "Insufficient disk space. Available: ${available_space}KB, Required: ${required_space}KB"
        exit 1
    fi
    
    success "Pre-deployment checks passed"
}

# Backup current deployment
backup_current_deployment() {
    log "Creating backup of current deployment..."
    
    local backup_name="backup-$(date +%Y%m%d-%H%M%S)"
    local backup_path="${DEPLOY_PATH}/../backups/${backup_name}"
    
    ssh -p ${DEPLOY_PORT} ${DEPLOYMENT_USER}@${DEPLOY_HOST} "
        mkdir -p ${DEPLOY_PATH}/../backups
        if [[ -d ${DEPLOY_PATH} ]]; then
            cp -r ${DEPLOY_PATH} ${backup_path}
            echo 'Backup created: ${backup_path}'
        else
            echo 'No existing deployment to backup'
        fi
    "
    
    # Store backup path for potential rollback
    echo "${backup_path}" > /tmp/last_backup_path
    
    success "Backup completed: ${backup_name}"
}

# Deploy application
deploy_application() {
    local version=$1
    local package_file="${PROJECT_ROOT}/quantum-software-${version}.tar.gz"
    
    log "Deploying AQUA V. Quantum Software ${version}..."
    
    # Stop service
    log "Stopping service: ${SERVICE_NAME}"
    ssh -p ${DEPLOY_PORT} ${DEPLOYMENT_USER}@${DEPLOY_HOST} "
        sudo systemctl stop ${SERVICE_NAME} || true
    "
    
    # Upload and extract package
    log "Uploading package..."
    scp -P ${DEPLOY_PORT} "${package_file}" ${DEPLOYMENT_USER}@${DEPLOY_HOST}:/tmp/
    
    ssh -p ${DEPLOY_PORT} ${DEPLOYMENT_USER}@${DEPLOY_HOST} "
        # Create deployment directory
        sudo mkdir -p ${DEPLOY_PATH}
        
        # Extract package
        cd /tmp
        tar -xzf quantum-software-${version}.tar.gz
        
        # Deploy files
        sudo cp -r release/* ${DEPLOY_PATH}/
        sudo chown -R ${DEPLOYMENT_USER}:${DEPLOYMENT_USER} ${DEPLOY_PATH}
        sudo chmod +x ${DEPLOY_PATH}/bin/*
        
        # Update version file
        echo '${version}' | sudo tee ${DEPLOY_PATH}/VERSION
        
        # Clean up
        rm -f quantum-software-${version}.tar.gz
        rm -rf release/
    "
    
    # Update configuration
    log "Updating configuration..."
    ssh -p ${DEPLOY_PORT} ${DEPLOYMENT_USER}@${DEPLOY_HOST} "
        # Update service configuration if needed
        if [[ -f ${DEPLOY_PATH}/config/service.conf ]]; then
            sudo cp ${DEPLOY_PATH}/config/service.conf /etc/systemd/system/${SERVICE_NAME}.service
            sudo systemctl daemon-reload
        fi
    "
    
    success "Application deployed successfully"
}

# Start services
start_services() {
    log "Starting services..."
    
    ssh -p ${DEPLOY_PORT} ${DEPLOYMENT_USER}@${DEPLOY_HOST} "
        # Start main service
        sudo systemctl start ${SERVICE_NAME}
        sudo systemctl enable ${SERVICE_NAME}
        
        # Wait for service to be ready
        sleep 10
        
        # Check service status
        if sudo systemctl is-active --quiet ${SERVICE_NAME}; then
            echo 'Service started successfully'
        else
            echo 'Service failed to start'
            sudo systemctl status ${SERVICE_NAME}
            exit 1
        fi
    "
    
    success "Services started"
}

# Health check
health_check() {
    log "Performing health check..."
    
    local start_time=$(date +%s)
    local max_wait=${HEALTH_CHECK_TIMEOUT}
    
    while true; do
        local current_time=$(date +%s)
        local elapsed=$((current_time - start_time))
        
        if (( elapsed > max_wait )); then
            error "Health check timeout after ${max_wait} seconds"
            return 1
        fi
        
        # Check HTTP endpoint
        if curl -f -s -k --max-time 10 "${HEALTH_CHECK_URL}" > /dev/null 2>&1; then
            success "Health check passed"
            return 0
        fi
        
        log "Health check failed, retrying in 10 seconds... (${elapsed}/${max_wait}s)"
        sleep 10
    done
}

# Rollback deployment
rollback_deployment() {
    local backup_path=""
    
    if [[ -f /tmp/last_backup_path ]]; then
        backup_path=$(cat /tmp/last_backup_path)
    else
        error "No backup path found for rollback"
        return 1
    fi
    
    warning "Rolling back to backup: ${backup_path}"
    
    ssh -p ${DEPLOY_PORT} ${DEPLOYMENT_USER}@${DEPLOY_HOST} "
        # Stop current service
        sudo systemctl stop ${SERVICE_NAME} || true
        
        # Restore backup
        if [[ -d ${backup_path} ]]; then
            sudo rm -rf ${DEPLOY_PATH}
            sudo cp -r ${backup_path} ${DEPLOY_PATH}
            sudo chown -R ${DEPLOYMENT_USER}:${DEPLOYMENT_USER} ${DEPLOY_PATH}
            sudo chmod +x ${DEPLOY_PATH}/bin/*
            
            # Restart service
            sudo systemctl start ${SERVICE_NAME}
            
            echo 'Rollback completed'
        else
            echo 'Backup not found: ${backup_path}'
            exit 1
        fi
    "
    
    success "Rollback completed"
}

# Smoke test
smoke_test() {
    log "Running smoke tests..."
    
    # Basic connectivity test
    if ! curl -f -s -k --max-time 30 "${HEALTH_CHECK_URL}" > /dev/null; then
        error "Smoke test failed: Health endpoint not accessible"
        return 1
    fi
    
    # Test quantum service endpoints (if available)
    local quantum_test_url="${HEALTH_CHECK_URL%/health}/api/quantum/test"
    if curl -f -s -k --max-time 30 "${quantum_test_url}" > /dev/null 2>&1; then
        log "Quantum service endpoint accessible"
    else
        warning "Quantum service endpoint not accessible (may be expected)"
    fi
    
    success "Smoke tests passed"
}

# Main deployment function
main_deploy() {
    local environment=$1
    local version=$2
    local dry_run=$3
    local force=$4
    
    log "AQUA V. Quantum Software Deployment"
    log "===================================="
    log "Environment: ${environment}"
    log "Version: ${version}"
    log "Dry Run: ${dry_run}"
    log "Force: ${force}"
    log ""
    
    setup_environment "${environment}"
    
    if [[ "${dry_run}" == "true" ]]; then
        log "DRY RUN MODE - No actual changes will be made"
        log "Would deploy version ${version} to ${environment}"
        log "Package: ${PROJECT_ROOT}/quantum-software-${version}.tar.gz"
        log "Target: ${DEPLOY_HOST}:${DEPLOY_PATH}"
        return 0
    fi
    
    # Execute deployment steps
    pre_deployment_checks "${version}"
    backup_current_deployment
    deploy_application "${version}"
    start_services
    
    # Health check with rollback option
    if ! health_check; then
        if [[ "${force}" == "true" ]]; then
            warning "Health check failed but force flag is set, continuing..."
        else
            error "Health check failed, initiating rollback..."
            rollback_deployment
            exit 1
        fi
    fi
    
    # Final smoke test
    if ! smoke_test; then
        if [[ "${force}" == "false" ]]; then
            error "Smoke test failed, initiating rollback..."
            rollback_deployment
            exit 1
        fi
    fi
    
    success "Deployment completed successfully!"
    log "Version ${version} is now live on ${environment}"
}

# Parse command line arguments
if [[ $# -eq 0 ]]; then
    usage
    exit 1
fi

ENVIRONMENT=""
VERSION=""
DRY_RUN="false"
FORCE="false"
ROLLBACK="false"

while [[ $# -gt 0 ]]; do
    case $1 in
        --dry-run)
            DRY_RUN="true"
            shift
            ;;
        --force)
            FORCE="true"
            shift
            ;;
        --rollback)
            ROLLBACK="true"
            shift
            ;;
        --help)
            usage
            exit 0
            ;;
        *)
            if [[ -z "${ENVIRONMENT}" ]]; then
                ENVIRONMENT="$1"
            elif [[ -z "${VERSION}" ]] && [[ "${ROLLBACK}" == "false" ]]; then
                VERSION="$1"
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

if [[ "${ROLLBACK}" == "true" ]]; then
    log "Initiating rollback for environment: ${ENVIRONMENT}"
    setup_environment "${ENVIRONMENT}"
    rollback_deployment
    exit 0
fi

if [[ -z "${VERSION}" ]]; then
    error "Version is required"
    usage
    exit 1
fi

# Execute main deployment
main_deploy "${ENVIRONMENT}" "${VERSION}" "${DRY_RUN}" "${FORCE}"