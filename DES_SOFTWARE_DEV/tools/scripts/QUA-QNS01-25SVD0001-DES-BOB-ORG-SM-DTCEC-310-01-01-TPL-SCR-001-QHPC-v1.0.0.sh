#!/bin/bash
# Quantum Software Deployment Script
# Version: 1.0.0
# ATA-Chapter: DTCEC-310 (Scripts & Automation)

set -euo pipefail

# Script configuration
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
CONFIG_DIR="${PROJECT_ROOT}/tools/config"
LOG_DIR="/var/log/quantum-software"
TIMESTAMP=$(date +%Y%m%d_%H%M%S)

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Logging functions
log_info() {
    echo -e "${BLUE}[INFO]${NC} $(date '+%Y-%m-%d %H:%M:%S') - $*" | tee -a "${LOG_DIR}/deployment_${TIMESTAMP}.log"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $(date '+%Y-%m-%d %H:%M:%S') - $*" | tee -a "${LOG_DIR}/deployment_${TIMESTAMP}.log"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $(date '+%Y-%m-%d %H:%M:%S') - $*" | tee -a "${LOG_DIR}/deployment_${TIMESTAMP}.log"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $(date '+%Y-%m-%d %H:%M:%S') - $*" | tee -a "${LOG_DIR}/deployment_${TIMESTAMP}.log"
}

# Usage function
usage() {
    cat << EOF
Usage: $0 <environment> <version> [options]

Environments:
    development  Deploy to development environment
    staging      Deploy to staging environment
    production   Deploy to production environment

Options:
    -h, --help           Show this help message
    -d, --dry-run        Perform a dry run without actual deployment
    -f, --force          Force deployment without confirmation
    -r, --rollback       Rollback to previous version
    -c, --config FILE    Use custom configuration file
    -t, --timeout SEC    Set deployment timeout (default: 300)

Examples:
    $0 staging v1.0.0
    $0 production v1.0.0 --dry-run
    $0 staging v1.0.0 --rollback
EOF
}

# Parse command line arguments
parse_arguments() {
    if [[ $# -lt 2 ]]; then
        usage
        exit 1
    fi

    ENVIRONMENT=$1
    VERSION=$2
    shift 2

    # Default values
    DRY_RUN=false
    FORCE=false
    ROLLBACK=false
    CONFIG_FILE="${CONFIG_DIR}/deployment-${ENVIRONMENT}.yaml"
    TIMEOUT=300

    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                usage
                exit 0
                ;;
            -d|--dry-run)
                DRY_RUN=true
                shift
                ;;
            -f|--force)
                FORCE=true
                shift
                ;;
            -r|--rollback)
                ROLLBACK=true
                shift
                ;;
            -c|--config)
                CONFIG_FILE="$2"
                shift 2
                ;;
            -t|--timeout)
                TIMEOUT="$2"
                shift 2
                ;;
            *)
                log_error "Unknown option: $1"
                usage
                exit 1
                ;;
        esac
    done

    # Validate environment
    if [[ ! "$ENVIRONMENT" =~ ^(development|staging|production)$ ]]; then
        log_error "Invalid environment: $ENVIRONMENT"
        usage
        exit 1
    fi

    # Validate version format
    if [[ ! "$VERSION" =~ ^v[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
        log_error "Invalid version format: $VERSION (expected: vX.Y.Z)"
        exit 1
    fi
}

# Load configuration
load_configuration() {
    log_info "Loading configuration from: ${CONFIG_FILE}"
    
    if [[ ! -f "$CONFIG_FILE" ]]; then
        log_error "Configuration file not found: $CONFIG_FILE"
        exit 1
    fi

    # Parse YAML configuration (simplified - in production use proper YAML parser)
    DEPLOY_HOST=$(grep "host:" "$CONFIG_FILE" | awk '{print $2}')
    DEPLOY_PORT=$(grep "port:" "$CONFIG_FILE" | awk '{print $2}')
    DEPLOY_USER=$(grep "user:" "$CONFIG_FILE" | awk '{print $2}')
    DEPLOY_PATH=$(grep "path:" "$CONFIG_FILE" | awk '{print $2}')
    HEALTH_CHECK_URL=$(grep "health_check:" "$CONFIG_FILE" | awk '{print $2}')
    SERVICE_NAME=$(grep "service_name:" "$CONFIG_FILE" | awk '{print $2}')
}

# Pre-deployment checks
pre_deployment_checks() {
    log_info "Running pre-deployment checks..."
    
    # Check if artifact exists
    ARTIFACT_PATH="${PROJECT_ROOT}/artifacts/quantum-software-${VERSION}.tar.gz"
    if [[ ! -f "$ARTIFACT_PATH" ]]; then
        log_error "Artifact not found: $ARTIFACT_PATH"
        exit 1
    fi
    
    # Check disk space on target
    log_info "Checking disk space on target..."
    AVAILABLE_SPACE=$(ssh "${DEPLOY_USER}@${DEPLOY_HOST}" "df -BG ${DEPLOY_PATH} | tail -1 | awk '{print \$4}' | sed 's/G//'")
    if [[ $AVAILABLE_SPACE -lt 10 ]]; then
        log_error "Insufficient disk space on target: ${AVAILABLE_SPACE}GB available"
        exit 1
    fi
    
    # Check if service is running
    if ssh "${DEPLOY_USER}@${DEPLOY_HOST}" "systemctl is-active --quiet ${SERVICE_NAME}"; then
        log_info "Service ${SERVICE_NAME} is currently running"
        SERVICE_WAS_RUNNING=true
    else
        log_warning "Service ${SERVICE_NAME} is not running"
        SERVICE_WAS_RUNNING=false
    fi
    
    log_success "Pre-deployment checks passed"
}

# Backup current deployment
backup_current() {
    log_info "Creating backup of current deployment..."
    
    if [[ "$DRY_RUN" == "true" ]]; then
        log_info "[DRY RUN] Would create backup at: ${DEPLOY_PATH}/backups/backup_${TIMESTAMP}"
        return
    fi
    
    ssh "${DEPLOY_USER}@${DEPLOY_HOST}" << EOF
        set -e
        if [[ -d "${DEPLOY_PATH}/current" ]]; then
            mkdir -p "${DEPLOY_PATH}/backups"
            cp -r "${DEPLOY_PATH}/current" "${DEPLOY_PATH}/backups/backup_${TIMESTAMP}"
            echo "Backup created: ${DEPLOY_PATH}/backups/backup_${TIMESTAMP}"
        else
            echo "No current deployment to backup"
        fi
EOF
    
    log_success "Backup completed"
}

# Deploy new version
deploy_version() {
    log_info "Deploying version ${VERSION}..."
    
    if [[ "$DRY_RUN" == "true" ]]; then
        log_info "[DRY RUN] Would deploy to: ${DEPLOY_PATH}/releases/${VERSION}"
        return
    fi
    
    # Create release directory
    ssh "${DEPLOY_USER}@${DEPLOY_HOST}" "mkdir -p ${DEPLOY_PATH}/releases/${VERSION}"
    
    # Copy artifact to target
    log_info "Copying artifact to target..."
    scp "$ARTIFACT_PATH" "${DEPLOY_USER}@${DEPLOY_HOST}:${DEPLOY_PATH}/releases/${VERSION}/"
    
    # Extract and setup
    log_info "Extracting and setting up..."
    ssh "${DEPLOY_USER}@${DEPLOY_HOST}" << EOF
        set -e
        cd "${DEPLOY_PATH}/releases/${VERSION}"
        tar -xzf "quantum-software-${VERSION}.tar.gz"
        rm "quantum-software-${VERSION}.tar.gz"
        
        # Set permissions
        chmod +x release/bin/*
        
        # Create symlinks for configuration
        ln -sf "${DEPLOY_PATH}/shared/config" release/config/local
        ln -sf "${DEPLOY_PATH}/shared/logs" release/logs
EOF
    
    log_success "Version ${VERSION} deployed"
}

# Switch to new version
switch_version() {
    log_info "Switching to version ${VERSION}..."
    
    if [[ "$DRY_RUN" == "true" ]]; then
        log_info "[DRY RUN] Would switch symlink to: ${DEPLOY_PATH}/releases/${VERSION}/release"
        return
    fi
    
    # Stop service if running
    if [[ "$SERVICE_WAS_RUNNING" == "true" ]]; then
        log_info "Stopping service ${SERVICE_NAME}..."
        ssh "${DEPLOY_USER}@${DEPLOY_HOST}" "sudo systemctl stop ${SERVICE_NAME}"
    fi
    
    # Switch symlink
    ssh "${DEPLOY_USER}@${DEPLOY_HOST}" << EOF
        set -e
        cd "${DEPLOY_PATH}"
        rm -f current
        ln -sf "releases/${VERSION}/release" current
        echo "Switched to version ${VERSION}"
EOF
    
    # Start service
    log_info "Starting service ${SERVICE_NAME}..."
    ssh "${DEPLOY_USER}@${DEPLOY_HOST}" "sudo systemctl start ${SERVICE_NAME}"
    
    # Wait for service to be ready
    sleep 5
    
    log_success "Version switch completed"
}

# Health check
health_check() {
    log_info "Running health check..."
    
    if [[ "$DRY_RUN" == "true" ]]; then
        log_info "[DRY RUN] Would check: ${HEALTH_CHECK_URL}"
        return
    fi
    
    local max_attempts=30
    local attempt=1
    
    while [[ $attempt -le $max_attempts ]]; do
        if curl -sf "${HEALTH_CHECK_URL}" > /dev/null; then
            log_success "Health check passed"
            return 0
        fi
        
        log_warning "Health check attempt ${attempt}/${max_attempts} failed"
        sleep 2
        ((attempt++))
    done
    
    log_error "Health check failed after ${max_attempts} attempts"
    return 1
}

# Rollback deployment
rollback_deployment() {
    log_error "Rolling back deployment..."
    
    if [[ "$DRY_RUN" == "true" ]]; then
        log_info "[DRY RUN] Would rollback to previous version"
        return
    fi
    
    # Find previous version
    PREVIOUS_VERSION=$(ssh "${DEPLOY_USER}@${DEPLOY_HOST}" "ls -t ${DEPLOY_PATH}/backups | head -1")
    
    if [[ -z "$PREVIOUS_VERSION" ]]; then
        log_error "No backup version found for rollback"
        exit 1
    fi
    
    # Stop service
    ssh "${DEPLOY_USER}@${DEPLOY_HOST}" "sudo systemctl stop ${SERVICE_NAME}"
    
    # Restore from backup
    ssh "${DEPLOY_USER}@${DEPLOY_HOST}" << EOF
        set -e
        cd "${DEPLOY_PATH}"
        rm -f current
        cp -r "backups/${PREVIOUS_VERSION}" current
        echo "Rolled back to: ${PREVIOUS_VERSION}"
EOF
    
    # Start service
    ssh "${DEPLOY_USER}@${DEPLOY_HOST}" "sudo systemctl start ${SERVICE_NAME}"
    
    log_success "Rollback completed"
}

# Cleanup old releases
cleanup_old_releases() {
    log_info "Cleaning up old releases..."
    
    if [[ "$DRY_RUN" == "true" ]]; then
        log_info "[DRY RUN] Would clean up old releases"
        return
    fi
    
    # Keep last 5 releases
    ssh "${DEPLOY_USER}@${DEPLOY_HOST}" << EOF
        set -e
        cd "${DEPLOY_PATH}/releases"
        ls -t | tail -n +6 | xargs -r rm -rf
        
        cd "${DEPLOY_PATH}/backups"
        ls -t | tail -n +6 | xargs -r rm -rf
EOF
    
    log_success "Cleanup completed"
}

# Main deployment function
main() {
    # Create log directory
    mkdir -p "$LOG_DIR"
    
    # Parse arguments
    parse_arguments "$@"
    
    log_info "Starting deployment process..."
    log_info "Environment: ${ENVIRONMENT}"
    log_info "Version: ${VERSION}"
    log_info "Dry Run: ${DRY_RUN}"
    
    # Load configuration
    load_configuration
    
    # Confirmation prompt
    if [[ "$FORCE" != "true" && "$DRY_RUN" != "true" ]]; then
        echo -e "${YELLOW}Warning: You are about to deploy to ${ENVIRONMENT}${NC}"
        read -p "Are you sure you want to continue? (yes/no): " confirmation
        if [[ "$confirmation" != "yes" ]]; then
            log_info "Deployment cancelled by user"
            exit 0
        fi
    fi
    
    # Execute deployment steps
    if [[ "$ROLLBACK" == "true" ]]; then
        rollback_deployment
    else
        pre_deployment_checks
        backup_current
        deploy_version
        switch_version
        
        if health_check; then
            cleanup_old_releases
            log_success "Deployment completed successfully!"
        else
            log_error "Deployment failed health check"
            rollback_deployment
            exit 1
        fi
    fi
}

# Execute main function
main "$@"
