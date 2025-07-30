# AQUA V. Quantum Navigation System - Convenience Makefile
# Document: QUA-QNS01-25SVD0001-DES-BOB-ORG-TD-DTCEC-304-00-02-TPL-BLD-001-QDAT-v1.0.0.mk
# Owner: QDAT (Data Governance Division)
# Site: Silicon Valley (25SVD)
# =============================================================================
# Copyright (C) 2025 GAIA AIR - ROBBBO-T
# Aerospace and Quantum United Advanced Venture (AQUA V.)
# =============================================================================
# This Makefile provides convenient shortcuts for common build operations
# It wraps CMake commands for the Quantum Navigation System build process
# =============================================================================

# Build configuration
BUILD_DIR ?= build
BUILD_TYPE ?= Release
INSTALL_PREFIX ?= /opt/aqua-v/qns
GENERATOR ?= "Unix Makefiles"
VERBOSE ?= 0

# Parallel jobs (default to number of CPU cores)
JOBS ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# CMake executable
CMAKE ?= cmake
CTEST ?= ctest
CPACK ?= cpack

# AQUA V. specific options
ENABLE_QUANTUM_HARDWARE ?= OFF
ENABLE_QUANTUM_SIMULATOR ?= ON
ENABLE_ALI_BOB_SYNC ?= ON
QNS_UPDATE_RATE ?= 1000

# Color output
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
NC := \033[0m # No Color

# Default target
.DEFAULT_GOAL := all

# =============================================================================
# MAIN TARGETS
# =============================================================================

.PHONY: all
all: build
	@echo "$(GREEN)✓ AQUA V. QNS build complete$(NC)"

.PHONY: help
help:
	@echo "$(BLUE)AQUA V. Quantum Navigation System - Build System$(NC)"
	@echo "================================================="
	@echo "Main targets:"
	@echo "  make all            - Configure and build (default)"
	@echo "  make configure      - Configure build with CMake"
	@echo "  make build          - Build the project"
	@echo "  make test           - Run all tests"
	@echo "  make install        - Install to $(INSTALL_PREFIX)"
	@echo "  make package        - Create distribution packages"
	@echo "  make clean          - Clean build directory"
	@echo "  make distclean      - Remove build directory completely"
	@echo ""
	@echo "Development targets:"
	@echo "  make format         - Format source code"
	@echo "  make check          - Run static analysis"
	@echo "  make coverage       - Generate coverage report"
	@echo "  make docs           - Generate documentation"
	@echo "  make debug          - Build with debug configuration"
	@echo ""
	@echo "Quantum-specific targets:"
	@echo "  make quantum-test   - Run quantum validation tests"
	@echo "  make quantum-benchmark - Run quantum algorithm benchmarks"
	@echo "  make calibrate      - Run sensor calibration"
	@echo "  make flight-sim     - Run flight simulation tests"
	@echo ""
	@echo "Options:"
	@echo "  BUILD_DIR=$(BUILD_DIR)"
	@echo "  BUILD_TYPE=$(BUILD_TYPE)"
	@echo "  JOBS=$(JOBS)"
	@echo "  VERBOSE=$(VERBOSE)"
	@echo "  ENABLE_QUANTUM_HARDWARE=$(ENABLE_QUANTUM_HARDWARE)"

# =============================================================================
# BUILD TARGETS
# =============================================================================

.PHONY: configure
configure:
	@echo "$(BLUE)Configuring AQUA V. QNS build...$(NC)"
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) .. \
		-G $(GENERATOR) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX) \
		-DENABLE_QUANTUM_HARDWARE=$(ENABLE_QUANTUM_HARDWARE) \
		-DENABLE_QUANTUM_SIMULATOR=$(ENABLE_QUANTUM_SIMULATOR) \
		-DENABLE_ALI_BOB_SYNC=$(ENABLE_ALI_BOB_SYNC) \
		-DQNS_UPDATE_RATE_HZ=$(QNS_UPDATE_RATE)
	@echo "$(GREEN)✓ Configuration complete$(NC)"

.PHONY: build
build: configure
	@echo "$(BLUE)Building AQUA V. QNS...$(NC)"
	@$(CMAKE) --build $(BUILD_DIR) --parallel $(JOBS) --config $(BUILD_TYPE) $(if $(filter 1,$(VERBOSE)),--verbose)
	@echo "$(GREEN)✓ Build complete$(NC)"

.PHONY: rebuild
rebuild: clean build
	@echo "$(GREEN)✓ Rebuild complete$(NC)"

# =============================================================================
# TEST TARGETS
# =============================================================================

.PHONY: test
test: build
	@echo "$(BLUE)Running AQUA V. QNS tests...$(NC)"
	@cd $(BUILD_DIR) && $(CTEST) --output-on-failure -C $(BUILD_TYPE) $(if $(filter 1,$(VERBOSE)),-V)
	@echo "$(GREEN)✓ All tests passed$(NC)"

.PHONY: test-unit
test-unit: build
	@echo "$(BLUE)Running unit tests...$(NC)"
	@cd $(BUILD_DIR) && $(CTEST) -R "unit_" --output-on-failure

.PHONY: test-integration
test-integration: build
	@echo "$(BLUE)Running integration tests...$(NC)"
	@cd $(BUILD_DIR) && $(CTEST) -R "integration_" --output-on-failure

.PHONY: test-performance
test-performance: build
	@echo "$(BLUE)Running performance tests...$(NC)"
	@cd $(BUILD_DIR) && $(CTEST) -R "performance_" --output-on-failure

# =============================================================================
# QUANTUM-SPECIFIC TARGETS
# =============================================================================

.PHONY: quantum-test
quantum-test: build
	@echo "$(BLUE)Running quantum validation tests...$(NC)"
	@cd $(BUILD_DIR) && ./bin/quantum_validator --trl=6 --update-rate=$(QNS_UPDATE_RATE)
	@echo "$(GREEN)✓ Quantum validation complete$(NC)"

.PHONY: quantum-benchmark
quantum-benchmark: build
	@echo "$(BLUE)Running quantum algorithm benchmarks...$(NC)"
	@cd $(BUILD_DIR) && ./bin/performance_tests \
		--benchmark_filter="BM_Quantum.*" \
		--benchmark_format=console \
		--benchmark_out=quantum_benchmark_results.json \
		--benchmark_out_format=json
	@echo "$(GREEN)✓ Quantum benchmark complete. Results saved to $(BUILD_DIR)/quantum_benchmark_results.json$(NC)"

.PHONY: calibrate
calibrate: build
	@echo "$(BLUE)Running sensor calibration...$(NC)"
	@cd $(BUILD_DIR) && ./bin/aqua_v_qns --calibrate \
		--gravitometer-sensitivity=1e-12 \
		--magnetometer-range=1e-9
	@echo "$(GREEN)✓ Calibration complete$(NC)"

.PHONY: flight-sim
flight-sim: build
	@echo "$(BLUE)Running flight simulation tests...$(NC)"
	@cd $(BUILD_DIR) && ./bin/flight_simulator \
		--scenario=gps_denied \
		--scenario=urban_canyon \
		--scenario=magnetic_anomaly
	@echo "$(GREEN)✓ Flight simulation complete$(NC)"

# =============================================================================
# INSTALLATION TARGETS
# =============================================================================

.PHONY: install
install: build
	@echo "$(BLUE)Installing AQUA V. QNS to $(INSTALL_PREFIX)...$(NC)"
	@$(CMAKE) --install $(BUILD_DIR) --config $(BUILD_TYPE) $(if $(filter 1,$(VERBOSE)),--verbose)
	@echo "$(GREEN)✓ Installation complete$(NC)"

.PHONY: uninstall
uninstall:
	@echo "$(BLUE)Uninstalling AQUA V. QNS...$(NC)"
	@cd $(BUILD_DIR) && $(CMAKE) -P cmake_uninstall.cmake
	@echo "$(GREEN)✓ Uninstall complete$(NC)"

# =============================================================================
# PACKAGING TARGETS
# =============================================================================

.PHONY: package
package: build
	@echo "$(BLUE)Creating AQUA V. QNS packages...$(NC)"
	@cd $(BUILD_DIR) && $(CPACK) -C $(BUILD_TYPE) $(if $(filter 1,$(VERBOSE)),-V)
	@echo "$(GREEN)✓ Packages created in $(BUILD_DIR)$(NC)"

.PHONY: package-deb
package-deb: build
	@cd $(BUILD_DIR) && $(CPACK) -G DEB -C $(BUILD_TYPE)

.PHONY: package-rpm
package-rpm: build
	@cd $(BUILD_DIR) && $(CPACK) -G RPM -C $(BUILD_TYPE)

.PHONY: package-tgz
package-tgz: build
	@cd $(BUILD_DIR) && $(CPACK) -G TGZ -C $(BUILD_TYPE)

# =============================================================================
# DEVELOPMENT TARGETS
# =============================================================================

.PHONY: debug
debug:
	@$(MAKE) BUILD_TYPE=Debug all

.PHONY: release
release:
	@$(MAKE) BUILD_TYPE=Release all

.PHONY: format
format:
	@echo "$(BLUE)Formatting AQUA V. QNS source code...$(NC)"
	@find src tests -name "*.cpp" -o -name "*.h" -o -name "*.hpp" | \
		xargs clang-format -i -style=file
	@echo "$(GREEN)✓ Code formatting complete$(NC)"

.PHONY: check
check:
	@echo "$(BLUE)Running static analysis...$(NC)"
	@cppcheck --enable=all \
		--suppress=missingInclude \
		--error-exitcode=1 \
		--inline-suppr \
		--project=$(BUILD_DIR)/compile_commands.json \
		--report-progress \
		src/
	@echo "$(GREEN)✓ Static analysis complete$(NC)"

.PHONY: coverage
coverage:
	@echo "$(BLUE)Generating coverage report...$(NC)"
	@$(MAKE) BUILD_TYPE=Debug EXTRA_FLAGS="-DENABLE_COVERAGE=ON" build
	@cd $(BUILD_DIR) && $(MAKE) coverage
	@echo "$(GREEN)✓ Coverage report available in $(BUILD_DIR)/coverage$(NC)"

.PHONY: docs
docs: configure
	@echo "$(BLUE)Generating documentation...$(NC)"
	@cd $(BUILD_DIR) && $(MAKE) docs
	@echo "$(GREEN)✓ Documentation generated in $(BUILD_DIR)/docs$(NC)"

# =============================================================================
# CLEANING TARGETS
# =============================================================================

.PHONY: clean
clean:
	@echo "$(BLUE)Cleaning build artifacts...$(NC)"
	@if [ -d $(BUILD_DIR) ]; then \
		$(CMAKE) --build $(BUILD_DIR) --target clean; \
	fi
	@echo "$(GREEN)✓ Clean complete$(NC)"

.PHONY: distclean
distclean:
	@echo "$(BLUE)Removing build directory...$(NC)"
	@rm -rf $(BUILD_DIR)
	@rm -f compile_commands.json
	@rm -f .cache
	@echo "$(GREEN)✓ Distribution clean complete$(NC)"

# =============================================================================
# UTILITY TARGETS
# =============================================================================

.PHONY: info
info:
	@echo "$(BLUE)AQUA V. QNS Build Information$(NC)"
	@echo "=============================="
	@echo "Program: Quantum Navigation System (QNS)"
	@echo "TRL: 6 (Flight Testing)"
	@echo "Site: Silicon Valley (25SVD)"
	@echo "Update Rate: $(QNS_UPDATE_RATE) Hz"
	@echo "Build Directory: $(BUILD_DIR)"
	@echo "Build Type: $(BUILD_TYPE)"
	@echo "Install Prefix: $(INSTALL_PREFIX)"
	@echo "Parallel Jobs: $(JOBS)"
	@echo "Quantum Hardware: $(ENABLE_QUANTUM_HARDWARE)"
	@echo "Quantum Simulator: $(ENABLE_QUANTUM_SIMULATOR)"

.PHONY: version
version:
	@cd $(BUILD_DIR) && ./bin/aqua_v_qns --version

.PHONY: run
run: build
	@echo "$(BLUE)Starting AQUA V. QNS...$(NC)"
	@cd $(BUILD_DIR) && ./bin/aqua_v_qns

# =============================================================================
# CONTINUOUS INTEGRATION TARGETS
# =============================================================================

.PHONY: ci
ci: clean configure build test package
	@echo "$(GREEN)✓ CI pipeline complete$(NC)"

.PHONY: ci-quick
ci-quick: build test-unit
	@echo "$(GREEN)✓ Quick CI complete$(NC)"

# Prevent make from treating arguments as targets
%:
	@:

# EOF
