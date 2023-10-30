# Supported types are "Debug" and "Release". See "src/CMakeLists.txt"
BUILD_TYPE ?= Debug

# Output ELF file path
BUILD_ELF_PATH = build/src/application

# Output binary image path
OUTPUT_BINARY_IMAGE_PATH = build/src/application.bin

# GCC toolchain
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Default build target
build:
	mkdir -p build && \
		cd build && \
		cmake -DBUILD_TYPE=$(BUILD_TYPE) .. && \
		make -j$$(nproc)
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

image:
	@echo Prepare image for uploading onto target
	$(OBJCOPY) -O binary $(BUILD_ELF_PATH) $(OUTPUT_BINARY_IMAGE_PATH)
	@echo Saved output binary at $(OUTPUT_BINARY_IMAGE_PATH)
