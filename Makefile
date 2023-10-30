# Supported types are "Debug" and "Release". See "src/CMakeLists.txt"
BUILD_TYPE ?= Debug

# Output ELF file path
BUILD_ELF_PATH = build/usbad

# Default build target
build:
	mkdir -p build && \
		cd build && \
		cmake -DBUILD_TYPE=$(BUILD_TYPE) .. && \
		make -j$$(nproc)
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
