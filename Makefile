# Supported types are "Debug" and "Release". See "src/CMakeLists.txt"
BUILD_TYPE ?= Debug

# Output ELF file path
BUILD_ELF_PATH = build/src/common/application

# Output binary image path
OUTPUT_BINARY_IMAGE_PATH = build/src/common/application.bin

# GCC toolchain
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Default build target
build:
	mkdir -p build && \
		cd build && \
		cmake -DBUILD_TYPE=$(BUILD_TYPE) -DUSE_STM32F407IG_TARGET=ON .. && \
		VERBOSE=1 make -j$$(nproc)
	$(SIZE) $(BUILD_ELF_PATH)
.PHONY: build

clean:
	cd build && \
		make clean

distclean:
	rm -rf build

disassemble:
	$(OBJDUMP) -dt $(BUILD_ELF_PATH)

disassemble_all:
	$(OBJDUMP) -Dt $(BUILD_ELF_PATH)

image: build
	@echo Prepare image for uploading onto target
	$(OBJCOPY) -O binary $(BUILD_ELF_PATH) $(OUTPUT_BINARY_IMAGE_PATH)
	@echo Saved output binary at $(OUTPUT_BINARY_IMAGE_PATH)

run_qemu: image
	bash tools/run_qemu.sh
