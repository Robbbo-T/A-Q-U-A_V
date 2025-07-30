# Convenience Makefile for AQUA V. QNS

.PHONY: all clean build test install package docs format check

BUILD_DIR ?= build
BUILD_TYPE ?= Debug
JOBS ?= $(shell nproc)

all: build

configure:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build: configure
	@cd $(BUILD_DIR) && make -j$(JOBS)

test: build
	@cd $(BUILD_DIR) && ctest --output-on-failure

install: build
	@cd $(BUILD_DIR) && make install

package: build
	@cd $(BUILD_DIR) && cpack

docs:
	@cd $(BUILD_DIR) && make docs

clean:
	@rm -rf $(BUILD_DIR)

format:
	@find src tests -name "*.cpp" -o -name "*.h" | xargs clang-format -i

check:
	@cppcheck --enable=all --suppress=missingInclude src/
