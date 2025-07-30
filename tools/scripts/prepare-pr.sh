#!/bin/bash
# Script to prepare changes for Pull Request
# This helps ensure all files are properly staged and committed

set -euo pipefail

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${BLUE}Preparing DevOps Pipeline PR...${NC}"

# Check if we're in a git repository
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    echo -e "${RED}Error: Not in a git repository${NC}"
    exit 1
fi

# Get current branch
CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)
echo -e "${BLUE}Current branch: ${CURRENT_BRANCH}${NC}"

# Create feature branch if not already on one
if [ "$CURRENT_BRANCH" = "main" ] || [ "$CURRENT_BRANCH" = "master" ]; then
    FEATURE_BRANCH="feature/devops-pipeline-implementation"
    echo -e "${YELLOW}Creating feature branch: ${FEATURE_BRANCH}${NC}"
    git checkout -b "$FEATURE_BRANCH"
else
    FEATURE_BRANCH="$CURRENT_BRANCH"
fi

# Stage all DevOps-related files
echo -e "${BLUE}Staging DevOps pipeline files...${NC}"

# CI/CD Pipeline files
git add DES_SOFTWARE_DEV/build/ci/QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-CYB-812-00-01-TPL-CI-001-QDAT-v1.0.0.yml
git add DES_SOFTWARE_DEV/build/ci/QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-CYB-812-00-02-TPL-CI-002-QDAT-v1.0.0.dockerfile
git add DES_SOFTWARE_DEV/build/ci/QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-CYB-812-00-03-TPL-CI-003-QDAT-v1.0.0.groovy
git add DES_SOFTWARE_DEV/build/ci/QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-CYB-812-00-04-TPL-CI-004-QDAT-v1.0.0.properties

# Scripts
git add DES_SOFTWARE_DEV/tools/scripts/QUA-QNS01-25SVD0001-DES-BOB-ORG-SM-DTCEC-310-01-01-TPL-SCR-001-QHPC-v1.0.0.sh
git add DES_SOFTWARE_DEV/tools/scripts/QUA-QNS01-25SVD0001-DES-BOB-ORG-SM-DTCEC-310-01-02-TPL-SCR-001-QSCI-v1.0.0.py
git add DES_SOFTWARE_DEV/tools/scripts/setup-test-env.sh
git add DES_SOFTWARE_DEV/tools/scripts/validate-docs.py
git add tools/scripts/prepare-pr.sh

# Configuration files
git add DES_SOFTWARE_DEV/tools/config/QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-DTCEC-360-01-01-TPL-CFG-001-QDAT-v1.0.0.json
git add DES_SOFTWARE_DEV/tools/config/QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-DTCEC-360-01-02-TPL-CFG-001-QDAT-v1.0.0.yaml

# Project files
git add DES_SOFTWARE_DEV/QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-DTCEC-360-00-01-TPL-CFG-001-QDAT-v1.0.0.gitignore
git add .github/pull_request_template.md
git add .gitmessage

# Make scripts executable
chmod +x DES_SOFTWARE_DEV/tools/scripts/*.sh
chmod +x DES_SOFTWARE_DEV/tools/scripts/*.py

# Show status
echo -e "${BLUE}Git status:${NC}"
git status --short

# Commit changes
echo -e "${BLUE}Creating commit...${NC}"
git commit -m "feat(ci): add comprehensive DevOps pipeline implementation

- Add GitHub Actions workflow for CI/CD pipeline
- Add Jenkins pipeline configuration as alternative
- Create Docker environment for consistent builds
- Implement deployment scripts with rollback capability
- Add performance analysis and monitoring tools
- Configure test environments (unit, integration, performance)
- Add configuration management (JSON/YAML)
- Include documentation validation scripts
- Set up security scanning and quality checks

This implementation provides a complete DevOps pipeline covering:
1. Source code management and version control
2. Build automation with CMake
3. Automated testing framework
4. Static analysis and code quality checks
5. Documentation generation and validation
6. Artifact management
7. Deployment automation
8. Performance monitoring
9. Security compliance

Closes #1" || echo -e "${YELLOW}No changes to commit or commit failed${NC}"

# Push to remote
echo -e "${BLUE}Ready to push to remote repository${NC}"
echo -e "${YELLOW}To push your changes, run:${NC}"
echo -e "${GREEN}git push -u origin ${FEATURE_BRANCH}${NC}"

echo -e "\n${BLUE}After pushing, you can create a PR with this title and description:${NC}"
echo -e "${GREEN}Title: feat(ci): Add comprehensive DevOps pipeline implementation${NC}"
echo -e "\n${GREEN}Description:${NC}"
cat << 'EOF'
## Description
This PR implements a comprehensive DevOps pipeline for the Quantum Software Development project, providing end-to-end automation from code commit to production deployment.

## Type of Change
- [x] ✨ New feature (non-breaking change which adds functionality)
- [x] 🔨 Build/CI update
- [x] 📚 Documentation update
- [x] 🔧 Configuration change

## Changes Made
- Added multi-stage CI/CD pipeline using GitHub Actions
- Implemented Jenkins pipeline as an alternative CI/CD solution
- Created Docker environment for reproducible builds
- Developed deployment automation scripts with rollback capability
- Integrated performance analysis and monitoring tools
- Configured comprehensive testing framework
- Added security scanning and quality gates
- Implemented documentation validation

## Key Features

### 1. CI/CD Pipeline Stages
- **Stage 0**: Source code fetch and initialization
- **Stage 1**: Build environment setup using Docker
- **Stage 2**: Build process with CMake
- **Stage 3**: Static analysis and linting
- **Stage 4-6**: Unit, integration, and performance testing
- **Stage 7**: Documentation generation and validation
- **Stage 8**: Artifact generation and storage
- **Stage 9**: Deployment to staging/production

### 2. Build System
- CMake-based build configuration
- Docker containerization for consistency
- Support for multiple compilers (GCC, Clang)
- Parallel build optimization

### 3. Testing Framework
- Automated unit testing with coverage reports
- Integration testing with environment setup
- Performance testing with threshold validation
- Test result aggregation and reporting

### 4. Deployment Automation
- Zero-downtime deployment strategy
- Automatic rollback on failure
- Health check validation
- Multi-environment support (dev, staging, prod)

### 5. Monitoring and Analytics
- Performance metrics collection
- Real-time health monitoring
- Automated alerting
- Comprehensive logging

## Testing
- [x] Pipeline configuration validated
- [x] Docker build tested
- [x] Scripts syntax checked
- [x] Configuration files validated

## Technical Details

### Technologies Used
- **CI/CD**: GitHub Actions, Jenkins
- **Containerization**: Docker
- **Build**: CMake, Make
- **Languages**: C++, Python, Bash
- **Testing**: CTest, pytest
- **Analysis**: clang-tidy, cppcheck, SonarQube

### File Structure
```
DES_SOFTWARE_DEV/
├── build/ci/          # CI/CD pipeline configurations
├── tools/scripts/     # Automation scripts
├── tools/config/      # Configuration files
└── .github/           # GitHub-specific configurations
```

## Additional Notes
- All scripts follow the project's naming convention
- Configuration supports both YAML and JSON formats
- Pipeline is designed for quantum software specific requirements
- Includes quantum SDK integration and simulator support
EOF

echo -e "\n${GREEN}PR preparation complete!${NC}"
