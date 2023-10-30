BUILD_TYPE ?= DEBUG

all:
	mkdir -p build && \
		cd build && \
		cmake -DBUILD_TYPE=$(BUILD_TYPE) .. && \
		make -j$$(nproc)
