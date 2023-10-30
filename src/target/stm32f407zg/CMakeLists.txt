# Specify source files
file(GLOB SOURCES "./*.c" "./*.s")

# Build the library
add_library(stm32f407zg STATIC ${SOURCES})

# Set linker script
get_filename_component(LINKER_SCRIPT_PATH "./stm32f407zg.ld" REALPATH)

# Specify linker options
string(JOIN " " LINKER_OPTIONS
	"-Wl,-T,${LINKER_SCRIPT_PATH}"
	"-mcpu=cortex-m4"  # Target platform
	"-mlittle-endian"  # Use little-endian format
	"-ffreestanding"  # Imply there is no operating system, or standard library on the target platform
	"-nostartfiles"  # Do not run startup operations, such as setting global variables to their initial values. Do not use default startup files.
)

if (${BUILD_TYPE} STREQUAL "Debug")
	string(JOIN " " LINKER_OPTIONS
		${LINKER_OPTIONS}
		"-g3"
	)
endif()

message(STATUS "Using linker options: `${LINKER_OPTIONS}`")
target_link_options(stm32f407zg PUBLIC "SHELL:${LINKER_OPTIONS}")

# Specify compiler options
string(JOIN " " COMPILE_OPTIONS
	"-mthumb"  # Use thumb code
	"-mcpu=cortex-m3"  # Specify CPU architecture
)

if (${BUILD_TYPE} STREQUAL "Debug")
	string(JOIN " " COMPILE_OPTIONS
		${COMPILE_OPTIONS}
		"-g3"
	)
endif()

if (USE_STM32CUBEF4_LIBRARY)
	target_link_libraries(stm32f407zg PRIVATE stm32cubef4)
endif()

message(STATUS "Using compiler options: `${COMPILE_OPTIONS}`")
target_compile_options(stm32f407zg PUBLIC "SHELL:${COMPILE_OPTIONS}")
set_target_properties(stm32f407zg PROPERTIES LINKER_LANGUAGE C)
target_include_directories(stm32f407zg PRIVATE ${COMMON_INCLUDE_DIRECTORIES})
